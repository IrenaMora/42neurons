//
// Created by Irena Mora on 1/4/22.
//

/* Настоящий проект - пример использования библиотеки в распознавании изображений */
/* Программа предсказывает, какая цифра находится на черно-белом изображении 10 x 10 пикселей - нуль или единица */

#include <set>
#include <iostream>
/* Установка библиотеки для работы с изображениями */
/* Для MacOS: brew install imagemagick */
#include <Magick++.h>
/* Подключаем заголовочный файл библиотеки */
#include "../../42neurons.hpp"

/* Подключаем пространства имен */
using namespace std;
using namespace Magick;

/* Возвращает единицу, если пиксель является черным цветом */
inline int getPixelStatus(ColorRGB &pixel)
{
	return (pixel.red() && pixel.green() && pixel.blue());
}

/* Устанавливает значения (0 или 1) для всех входящих нейронов в зависимости от цвета пикселя */
void setNeuronsContainer(vector<NeuronIn> &in_neurons, string filename)
{
	/* Создаем счетчик, показывающий, какому нейрону выдаем статус (значение) в настоящий момент */
	int i = 0;
	try
	{
		/* Создание переменной, хращяней в дальнейшем цвет конкретного пикселя */
		ColorRGB pixel;
		/* Загружаем картинку для дальнейшего получения пикселей */
		Image image(filename);
		/* Получаем размер изображения (в нашем случае 10 пикселей) */
		int width_image = image.columns();
		/* Получаем размер изображения (в нашем случае 10 пикселей) */
		int height_image = image.rows();

		/* Перебираем каждый пиксель по одной координате */
		for (int height_current = 0; height_current < 10; height_current++)
		{
			/* Перебираем каждый пиксель по другой координате */
			for (int width_current = 0; width_current < 10; width_current++)
			{
				/* Получаем RGB пикселя по его координатам */
				pixel = image.pixelColor(width_current, height_current);
				/* Устанавливаем статус (значение) для входящего нейрона */
				/* 1 - если пиксель черный; 0 - если пиксель иного цвета */
				in_neurons.at(i).setStatus(getPixelStatus(pixel));
				/* Сдвигаем позицию для дальнейшего указания на то, к какому нейрону обращаемся */
				i++;
			}
		}
		/* Итого, перебрали каждый пиксель, установив каждому нейрону необходимый статус (значение) */
	}
	catch (Magick::Exception &e)
	{
		/* Выходим в случае ошибки */
		cerr << "Magick++ exception: " << e.what() << endl;
		exit(1);
	}
	catch (exception &e)
	{
		/* Выходим в случае ошибки */
		cerr << "Exception: " << e.what() << endl;
		exit(1);
	}
}

int	main()
{
	/* Инициализируем входные нейроны. Так как изображение 10 x 10, то количество нейронов - это 100 */
	vector<NeuronIn> in_neurons(100);
	/* Инициализируем глубокие нейроны для нуля */
	vector<NeuronDeep> deep_neurons_zero(100);
	/* Инициализируем глубокие нейроны для единицы */
	vector<NeuronDeep> deep_neurons_one(100);
	/* Инициализируем выходной нейрон для нуля, где будет содержаться предсказанный ответ */
	NeuronOut out_zero;
	/* Инициализируем выходной нейрон для единицы, где будет содержаться предсказанный ответ */
	NeuronOut out_one;

	/* Создаем нейронную сеть */
	NeuronNetwork network;

	/* Загружаем пустые нейроны */
	for (int i = 0; i < 100; i++)
		in_neurons.push_back(NeuronIn());
	/* Загружаем пустые нейроны */
	for (int i = 0; i < 100; i++)
		deep_neurons_zero.push_back(NeuronDeep());
	/* Загружаем пустые нейроны */
	for (int i = 0; i < 100; i++)
		deep_neurons_one.push_back(NeuronDeep());

	cout << "Neurons initialized" << endl;

	/* Добавляем в нейросеть вектор входящих нейронов */
	network.addNeurons(in_neurons);
	/* Добавляем в нейросеть вектор гулбоких нейронов */
	network.addNeurons(deep_neurons_zero);
	/* Добавляем в нейросеть вектор гулбоких нейронов */
	network.addNeurons(deep_neurons_one);
	/* Добавляем в нейросеть выходной нейрон */
	network.addNeuron(out_zero);
	/* Добавляем в нейросеть выходной нейрон */
	network.addNeuron(out_one);

	cout << "Neurons have been added" << endl;

	/* Перебираем каждый входной нейрон, создавая соединения */
	for (int i = 0; i < 100; i++)
	{
		/* Соединяем входные нейроны (хранящие информацию о цветах пикселей) с глубокими нейронами для нуля */
		/* Функция активации - ReLU, скорость обучения - 0.01 */
		network.createConnection(in_neurons.at(i), deep_neurons_zero.at(i), FunctionType::RELU, 0.01);
		/* Соединяем входные нейроны (хранящие информацию о цветах пикселей) с глубокими нейронами для единицы */
		/* Функция активации - ReLU, скорость обучения - 0.01 */
		network.createConnection(in_neurons.at(i), deep_neurons_one.at(i), FunctionType::RELU, 0.01);
		/* Соединяем глубокие нейроны для нуля с выходным нейроном для нуля */
		/* Функция активации - ReLU, скорость обучения - 0.01 */
		network.createConnection(deep_neurons_zero.at(i), out_zero, FunctionType::RELU, 0.01);
		/* Соединяем глубокие нейроны для единицы с выходным нейроном для единицы */
		/* Функция активации - ReLU, скорость обучения - 0.01 */
		network.createConnection(deep_neurons_one.at(i), out_one, FunctionType::RELU, 0.01);
	}

	cout << "Connections initialized" << endl;

	/* Выполняем обучение нейронной сети в цикле и тысячу раз */
	for (int i = 0; i < 1000; i++)
	{
		cout << "Learning loop №" << i << endl;

		/* Загружаем во входные нейроны пиксели из первого изображения с нулем */
		setNeuronsContainer(in_neurons, "./images/0/a.png");
		/* Сообщаем нейронной сети, что как результат мы хотим видеть ответ 1 (true, или правда) для нейрона с нулем, */
		/* потому как на изображении у нас действительно находится число нуль */
		out_zero.setExpectedStatus(1);
		/* Сообщаем нейронной сети, что как результат мы хотим видеть ответ 0 (false, или ложь) для нейрона с единицей, */
		/* потому как на изображении у нас находится не единица, а нуль */
		out_one.setExpectedStatus(0);
		/* Обучаем нейросеть, чтобы она подстроилась под наши ожидания, которые мы указали выше */
		network.learn();

		/* Загружаем во входные нейроны пиксели из первого изображения с единицей */
		setNeuronsContainer(in_neurons, "./images/1/a.png");
		/* Сообщаем нейронной сети, что как результат мы хотим видеть ответ 0 (false, или ложь) для нейрона с нулем, */
		/* потому как на изображении у нас находится не нуль, а единица */
		out_zero.setExpectedStatus(0);
		/* Сообщаем нейронной сети, что как результат мы хотим видеть ответ 1 (true, или правда) для нейрона с единицей, */
		/* потому как на изображении у нас действительно единица */
		out_one.setExpectedStatus(1);
		/* ... */
		network.learn();

		/* Загружаем во входные нейроны пиксели из второго изображения с нулем */
		setNeuronsContainer(in_neurons, "./images/0/b.png");
		/* ... */
		out_zero.setExpectedStatus(1);
		/* ... */
		out_one.setExpectedStatus(0);
		/* ... */
		network.learn();
		/* ... */

		/* ... и так далее повторяем те же действия... */

		setNeuronsContainer(in_neurons, "./images/1/b.png");
		out_zero.setExpectedStatus(0);
		out_one.setExpectedStatus(1);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/0/c.png");
		out_zero.setExpectedStatus(1);
		out_one.setExpectedStatus(0);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/1/c.png");
		out_zero.setExpectedStatus(0);
		out_one.setExpectedStatus(1);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/0/d.png");
		out_zero.setExpectedStatus(1);
		out_one.setExpectedStatus(0);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/1/d.png");
		out_zero.setExpectedStatus(0);
		out_one.setExpectedStatus(1);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/0/e.png");
		out_zero.setExpectedStatus(1);
		out_one.setExpectedStatus(0);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/1/e.png");
		out_zero.setExpectedStatus(0);
		out_one.setExpectedStatus(1);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/0/f.png");
		out_zero.setExpectedStatus(1);
		out_one.setExpectedStatus(0);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/1/f.png");
		out_zero.setExpectedStatus(0);
		out_one.setExpectedStatus(1);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/0/g.png");
		out_zero.setExpectedStatus(1);
		out_one.setExpectedStatus(0);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/1/g.png");
		out_zero.setExpectedStatus(0);
		out_one.setExpectedStatus(1);
		network.learn();
	}

	/* Нейросеть теперь обучена. Делаем две попытки распознать цифры со сторонних, ранее не изученных изображений */

	cout << endl << "Recognizing image 0.png" << endl;
	/* Загружаем во входные нейроны пиксели из изображения с нулем */
	setNeuronsContainer(in_neurons, "./images/forRecognition/0.png");
	/* Делаем просчет нейросети, а равно прогнозируем состояние нейронов, или наш ответ */
	network.compute();
	/* Выводим предсказанный ответ - число типа double, показывающее, насколько изображение похоже на нуль */
	/* Если ответ около единицы, это true (правда); иначе - ложь */
	cout << "\tIt is 0 - " << out_zero.getStatus() << endl;
	/* Выводим предсказанный ответ - число типа double, показывающее, насколько изображение похоже на единицу */
	/* Если ответ около единицы, это true (правда); иначе - ложь */
	cout << "\tIt is 1 - " << out_one.getStatus() << endl;

	cout << endl << "Recognizing image 1.png" << endl;
	/* Загружаем во входные нейроны пиксели из изображения с единицей */
	setNeuronsContainer(in_neurons, "./images/forRecognition/1.png");
	/* Делаем просчет нейросети, а равно прогнозируем состояние нейронов, или наш ответ */
	network.compute();
	/* Выводим предсказанный ответ - число типа double, показывающее, насколько изображение похоже на нуль */
	/* Если ответ около единицы, это true (правда); иначе - ложь */
	cout << "\tIt is 0 - " << out_zero.getStatus() << endl;
	/* Выводим предсказанный ответ - число типа double, показывающее, насколько изображение похоже на единицу */
	/* Если ответ около единицы, это true (правда); иначе - ложь */
	cout << "\tIt is 1 - " << out_one.getStatus() << endl;
}
