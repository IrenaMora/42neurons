/* Настоящий проект - пример использования библиотеки в распознавании изображений. */
/* Программа предсказывает, какая цифра находится на черно-белом изображении 20x20 пикселей. */

#include <set>
#include <iostream>
#include <string>

/* Установка библиотеки для работы с изображениями.
  Для MacOS:
	brew install pkg-config
	brew install imagemagick
*/
#include <Magick++.h>

/* Подключаем заголовочный файл библиотеки. */
#include "../../42neurons.hpp"

const int HEIGHT_PIXELS = 20;
const int WIDTH_PIXELS = 20;
const int DIGITS_LIMIT = 10;

/* Возвращает единицу, если пиксель является черным цветом. */
inline int getPixelStatus(const Magick::ColorRGB &pixel)
{
	return pixel.red() && pixel.green() && pixel.blue();
}

/* Устанавливает значения (0 или 1) для всех входящих нейронов в зависимости от цвета пикселя. */
void setNeuronsContainer(std::vector<NeuronIn> &in_neurons, const std::string &filename)
try
{
	/* Создание переменной, хращяней в дальнейшем цвет конкретного пикселя. */
	Magick::ColorRGB pixel;
	/* Загружаем картинку для дальнейшего получения пикселей. */
	Magick::Image image(filename);

	/* Перебираем каждый пиксель по одной координате. */
	for (auto current_width = 0; current_width != WIDTH_PIXELS; ++current_width)
	{
		/* Перебираем каждый пиксель по второй координате. */
		for (auto current_height = 0; current_height != HEIGHT_PIXELS; ++current_height)
		{
			/* Получаем RGB пикселя по его координатам. */
			pixel = image.pixelColor(current_width, current_height);
			/* Устанавливаем статус (значение) для входящего нейрона: */
			/* 		1 - если пиксель черный; 0 - если пиксель иного цвета. */
			in_neurons.at(current_height * HEIGHT_PIXELS + current_width).setStatus(getPixelStatus(pixel));
		}
	}
	/* Итого, перебрали каждый пиксель, установив каждому нейрону необходимый статус (значение). */
}
catch (const Magick::Exception &e)
{
	/* Выходим в случае ошибки Magick++. */
	std::cerr << "Magick++ exception: " << e.what() << '\n';
	exit(1);
}
catch (const std::exception &e)
{
	/* Выходим в случае иной ошибки. */
	std::cerr << "Exception: " << e.what() << '\n';
	exit(1);
}

int	main()
{
	/* Инициализируем входные нейроны. */
	std::vector<NeuronIn> in_neurons(HEIGHT_PIXELS * WIDTH_PIXELS);

	/* Инициализируем глубокие нейроны. */
	std::vector<std::vector<NeuronDeep>> deep_neurons(DIGITS_LIMIT, std::vector<NeuronDeep>(HEIGHT_PIXELS * WIDTH_PIXELS));

	/* Инициализируем выходные нейроны, где будут содержаться предсказанные ответы. */
	std::vector<NeuronOut> out_neurons(DIGITS_LIMIT);

	/* Создаем нейронную сеть */
	NeuronNetwork network;

	std::cout << "Neurons initialized" << std::endl;

	/* Добавляем в нейросеть вектор входящих нейронов. */
	network.addNeurons(in_neurons);

	/* Добавляем в нейросеть вектора гулбоких нейронов. */
	for (auto& deep_neuron : deep_neurons)
		network.addNeurons(deep_neuron);

	/* Добавляем в нейросеть выходные нейроны. */
	for (auto& neuron : out_neurons)
		network.addNeuron(neuron);

	std::cout << "Neurons have been added" << std::endl;

	/* Перебираем каждый входной нейрон, создавая соединения. */
	for (auto i = 0; i != HEIGHT_PIXELS * WIDTH_PIXELS; ++i)
	{
		/* Соединяем входные нейроны (хранящие информацию о цветах пикселей) с глубокими нейронами. */
		for (auto& deep_neuron : deep_neurons)
			network.createConnection(in_neurons.at(i), deep_neuron.at(i), FunctionType::RELU, 0.01);

		/* Соединяем глубокие нейроны с выходнымы нейронами. */
		for (auto j = 0; j != DIGITS_LIMIT; ++j) {
			network.createConnection(deep_neurons.at(j).at(i), out_neurons.at(j), FunctionType::RELU, 0.01);
		}
	}

	std::cout << "Connections initialized" << std::endl;

	/* Выполняем обучение нейронной сети. */
	for (auto epoch = 0; epoch != 1000; ++epoch)
	{
		if ((epoch + 1) % 50 == 0)
			std::cout << "Learning epoch #" << epoch + 1 << '\n';

		for (auto i = 0; i != DIGITS_LIMIT; ++i)
		{
			for (auto j = 'a'; j != 'h'; ++j)
			{
				/* Загружаем во входные нейроны пиксели из изображения. */
				setNeuronsContainer(in_neurons, "./images/" + std::to_string(i) + '/' + j + ".png");

				/* Сообщаем нейронной сети, что как результат мы хотим видеть ответ (true, или правда) для нейрона с i, */
				/* 		потому как на изображении у нас действительно находится число i. */
				for (auto k = 0; k != DIGITS_LIMIT; ++k)
					out_neurons.at(k).setExpectedStatus(i == k);

				/* Обучаем нейросеть, чтобы она подстроилась под наши ожидания, которые мы указали выше. */
				network.learn();
			}
		}
	}

	/* Нейросеть теперь обучена. Делаем попытки распознать цифры со сторонних, ранее не изученных изображений: */
	for (auto i = 0; i != DIGITS_LIMIT; ++i)
	{
		std::cout << "\nRecognizing image " << i << ".png\n";

		/* Загружаем во входные нейроны пиксели из изображения. */
		setNeuronsContainer(in_neurons, "./images/forRecognition/" + std::to_string(i) + ".png");

		/* Делаем просчет нейросети, (прогнозируем состояние нейронов == наш ответ). */
		network.compute();

		/* Выводим предсказанный ответ - число типа double, показывающее, насколько изображение похоже на конкретное число. */
		for (auto j = 0; j != DIGITS_LIMIT; ++j)
			std::cout << "\tIt is " << j << " - " << out_neurons.at(j).getStatus() << '\n';
	}
}
