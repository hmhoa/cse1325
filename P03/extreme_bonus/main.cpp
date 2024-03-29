#include <iostream> //for cin, cout, string
#include <algorithm> //for sort
#include <vector> //for vector and methods push_back, begin, end
#include "color.h"

int main()
{
	std::vector<Color> colors = { Color::BLACK, Color::RED, Color::GREEN, Color::BLUE, Color::CYAN, Color::MAGENTA, Color::YELLOW, Color::GRAY, Color::WHITE };
	Color bg_cyan{0,255,255,true}; //cyan background color
	Color bg_white{255,255,255,true}; //white background color

	//output comparisons for previous color
	std::cout << colors[0] << bg_white << colors[0].to_string() << Color::RESET << std::endl;
	std::string output;
	for(int i=1; i<colors.size(); ++i)
	{
		output = " ";
		if(colors[i] == colors[i-1]) output += "== ";
		if(colors[i] != colors[i-1]) output += "!= ";
		if(colors[i] < colors[i-1]) output += "< ";
		if(colors[i] <= colors[i-1]) output += "<= ";
		if(colors[i] > colors[i-1]) output += "> ";
		if(colors[i] >= colors[i-1]) output += ">= ";

		output += "in subjective brightness to the previous color";
		std::cout << colors[i] << colors[i].to_string() << Color::RESET << output << std::endl;	
	}

	//testing + and - operators
	Color pink = colors[1] + 128;
	Color dark_red = colors[1] - 128;
	Color babl = 128 + colors[3];
	
	std::cout << pink << pink.to_string() << Color::RESET << " = " << colors[1] << colors[1].to_string() << Color::RESET << " + 128\n"
		 << babl << babl.to_string() << Color::RESET << " = 128 + " << colors[3] << colors[3].to_string() << "\n" 
		 << dark_red << dark_red.to_string() << Color::RESET << " = " << colors[1] << colors[1].to_string() << Color::RESET << " - 128" << std::endl;

	//color blending and de-blending tests via * and / operators
	Color yellow = Color::YELLOW;
	Color red = Color::RED;
	Color orange = red * yellow;
	Color red2 = orange/yellow;

	std::cout << orange << orange.to_string() << Color::RESET << " = " << red << red.to_string() << Color::RESET << " * " << yellow << yellow.to_string() << "\n"
		<< red2 << red2.to_string() << Color::RESET << " = " << orange << orange.to_string() << Color::RESET << " / " << yellow << yellow.to_string() << std::endl;

	std::cout << colors[4] << bg_white << "CYAN\t" << colors[8] << bg_cyan << "WHITE" << Color::RESET << std::endl;

	//cyan to white for fun
	Color color = Color::CYAN;
	while(color != Color::WHITE)
	{
		color = color + 16;		
		std::cout << color << color.to_string() << std::endl;
	}

	//last few lines - testing increment and decrement
	color = Color::RED;
	std::cout << ++color << color.to_string() << Color::RESET << " Pre-Increment\n" 
		<< color++ << color.to_string() << Color::RESET << " Post-Increment\n"
		<< --color << color.to_string() << Color::RESET << " Pre-Decrement\n"
		<< color-- << color.to_string() << Color::RESET << " Post-Decrement" 			<< std::endl;

	//black to white and white to black
	color = Color::BLACK;
	while(color != Color::WHITE)
	{
		++color;
		std::cout << color << "+";
	}
	while(color != Color::BLACK)
	{
		--color;
		std::cout << color << "-";
	}

	//reset the terminal color
	std::cout << Color::RESET << std::endl;

	return 0;
}
