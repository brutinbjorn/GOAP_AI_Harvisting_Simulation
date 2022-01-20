// GOAP_AI_HarvistingSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GOAP_Application.h"
#include "vld.h"
#include <string>

int main()
{
    std::cout << "Hello GOAP AI\n";
	GOAP_Application* m_pApplictation = new GOAP_Application();
	
	m_pApplictation->Start();
    std::string input;
    std::string ch;
    do
    {

        std::cout << std::endl;
        std::cin.clear();
    	
        ch = std::cin.get();

    	int turnsToTake = 0;
        try
        {
            turnsToTake = std::stoi(ch);
        }
        catch (std::invalid_argument a)
        {
            std::cout << "type a integer number for seconds to pass, \n or x to close the program ";
        }

        if (ch[0] != 'x' && turnsToTake > 0)
        {

            for (int i = 0; i < turnsToTake * 4; i++)
            {
				std::cout << "0,25 seconds" << std::endl;
				m_pApplictation->Update(0.25f);
            }
        }

    	
    }
    while (ch[0] != 'x');

    delete m_pApplictation;

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
