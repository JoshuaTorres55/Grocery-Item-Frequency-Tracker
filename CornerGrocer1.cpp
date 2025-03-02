/*
Project: CornerGrocer1
Author: Joshua Torres
Date: February 22, 2025
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void displayMenu() {
	std::cout << "\nCorner Grocer Menu:\n";
	std::cout << "1. Display all items purchased with frequencies\n";
	std::cout << "2. Search for specific item's frequency\n";
	std::cout << "3. Output data to a file\n";
	std::cout << "4. Exit\n";
	std::cout << "Enter your choice: ";
}

void readSalesData(const std::string& filename, std::unordered_map<std::string, int>& salesData) {
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file '" << filename << "'\n";
		return;
	}

	std::string item;
	while (inputFile >> item) {
		salesData[item]++;
	}

	inputFile.close();
}

void displayAllItems(const std::unordered_map<std::string, int>& salesData) {
	std::cout << "\nItems Purchased and Their Frequencies:\n";
	for (const auto& pair : salesData) {
		std::cout << pair.first << ": " << pair.second << "\n";
	}
}

void searchItemFrequency(const std::unordered_map<std::string, int>& salesData) {
	std::string item;
	std::cout << "\nEnter the item name: ";
	std::cin >> item;

	auto it = salesData.find(item);
	if (it != salesData.end()) {
		std::cout << item << " was purchased " << it->second << " time(s).\n";
	}
	else {
		std::cout << item << " was not found in the sales data.\n";
	}
}

void outputToFile(const std::unordered_map<std::string, int>& salesData, const std::string& outputFilename) {
	std::ofstream outputFile(outputFilename);
	if (!outputFile.is_open()) {
		std::cerr << "Error: Unable to create file '" << outputFilename << "'\n";
		return;
	}

	for (const auto& pair : salesData) {
		outputFile << pair.first << ": " << pair.second << "\n";
	}

	outputFile.close();
	std::cout << "Data has been written to '" << outputFilename << "'\n";
}

int main() {
	std::unordered_map<std::string, int> salesData;
	const std::string inputFilename = "CS210_Project_Three_Input_File.txt";
	const std::string outputFilename = "frequency.dat";

	// Load data from file
	readSalesData(inputFilename, salesData);

	int choice = 0;
	while (choice != 4) {
		displayMenu();
		std::cin >> choice;

		switch (choice) {
		case 1:
			displayAllItems(salesData);
			break;
		case 2:
			searchItemFrequency(salesData);
			break;
		case 3:
			outputToFile(salesData, outputFilename);
			break;
		case 4:
			std::cout << "Exiting program. Goodbye!\n";
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}