//
// Created by Irena Mora on 1/4/22.
//

/*  */

#include <set>
#include <iostream>
/* Установка библиотеки для работы с изображениями */
/* Для MacOS: brew install imagemagick */
#include <Magick++.h>
//#include "../../42neurons.hpp"

using namespace std;
using namespace Magick;

/* Возвращает, является ли пиксель черным цветом */
inline int getPixelStatus(ColorRGB &pixel)
{
	return (pixel.red() && pixel.green() && pixel.blue());
}

/* Возвращает, является ли пиксель черным цветом */
void setNeuronsContainer(vector<NeuronIn> &in_neurons, string filename)
{
	int i = 0;
	try
	{
		ColorRGB pixel;
		Image image(filename);
		int width_image = image.columns();
		int height_image = image.rows();

		for (int height_current = 0; height_current < 10; height_current++)
		{
			for (int width_current = 0; width_current < 10; width_current++)
			{
				pixel = image.pixelColor(width_current, height_current);
				in_neurons.at(i).setStatus(getPixelStatus(pixel));
				i++;
			}
		}
	}
	catch (Magick::Exception &e)
	{
		cerr << "Magick++ exception: " << e.what() << endl;
		exit(1);
	}
	catch (exception &e)
	{
		cerr << "Exception: " << e.what() << endl;
		exit(1);
	}
}

int	main()
{
	vector<NeuronIn> in_neurons;
	vector<NeuronDeep> deep_neurons_zero;
	vector<NeuronDeep> deep_neurons_one;
	NeuronOut out_zero;
	NeuronOut out_one;

	NeuronNetwork network;

	in_neurons.reserve(100);
	deep_neurons_zero.reserve(100);
	deep_neurons_one.reserve(100);

	for (int i = 0; i < 100; i++)
		in_neurons.push_back(NeuronIn());
	for (int i = 0; i < 100; i++)
		deep_neurons_zero.push_back(NeuronDeep());
	for (int i = 0; i < 100; i++)
		deep_neurons_one.push_back(NeuronDeep());

	cout << "Neurons initialized" << endl;

	network.addNeurons(in_neurons);
	network.addNeurons(deep_neurons_zero);
	network.addNeurons(deep_neurons_one);
	network.addNeuron(out_zero);
	network.addNeuron(out_one);

	cout << "Neurons have been added" << endl;

	for (int i = 0; i < 100; i++)
	{
		network.createConnection(in_neurons.at(i), deep_neurons_zero.at(i), FunctionType::RELU, 0.01);
		network.createConnection(in_neurons.at(i), deep_neurons_one.at(i), FunctionType::RELU, 0.01);
		network.createConnection(deep_neurons_zero.at(i), out_zero, FunctionType::RELU, 0.01);
		network.createConnection(deep_neurons_one.at(i), out_one, FunctionType::RELU, 0.01);
	}

	cout << "Connections initialized" << endl;

	for (int i = 0; i < 1000; i++)
	{
		cout << "Learning loop №" << i << endl;

		setNeuronsContainer(in_neurons, "./images/0/a.png");
		out_zero.setExpectedStatus(1);
		out_one.setExpectedStatus(0);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/1/a.png");
		out_zero.setExpectedStatus(0);
		out_one.setExpectedStatus(1);
		network.learn();

		setNeuronsContainer(in_neurons, "./images/0/b.png");
		out_zero.setExpectedStatus(1);
		out_one.setExpectedStatus(0);
		network.learn();

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

	cout << endl << "Recognizing image 0.png" << endl;
	setNeuronsContainer(in_neurons, "./images/forRecognition/0.png");
	network.compute();
	cout << "\tIt is 0 - " << out_zero.getStatus() << endl;
	cout << "\tIt is 1 - " << out_one.getStatus() << endl;

	cout << endl << "Recognizing image 1.png" << endl;
	setNeuronsContainer(in_neurons, "./images/forRecognition/1.png");
	network.compute();
	cout << "\tIt is 0 - " << out_zero.getStatus() << endl;
	cout << "\tIt is 1 - " << out_one.getStatus() << endl;
}
