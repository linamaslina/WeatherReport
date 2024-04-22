#include <iostream>
#include <fstream>
#include<vector>
#include <sstream>
#include <string>
#include "Weather.h"

static unsigned fileNumber = 0;

Weather FindBestPort(Weather firstLocation, Weather secondLocation)
{
	if (firstLocation.GetLocation() == "Kourou" ||
		firstLocation.GetLocation() == "Tanegashima" || 
		firstLocation.GetLocation() == "CapeCanaveral" || 
		firstLocation.GetLocation() == "Kodiak")
		return firstLocation;

	if (secondLocation.GetLocation() == "Kourou" ||
		secondLocation.GetLocation() == "Tanegashima" ||
		secondLocation.GetLocation() == "CapeCanaveral" ||
		secondLocation.GetLocation() == "Kodiak")
		return secondLocation;
}

//returns the best day out of all locations 
void GetBestDay(Weather locations[]) 
{
	Weather bestLocation;
	for (unsigned i = 0; i < 4; i++)
	{
		if (bestLocation.GetBestScore() == 0 || bestLocation.GetBestScore() > locations[i].GetBestScore())
			bestLocation = locations[i];
		else if (bestLocation.GetBestScore() == locations[i].GetBestScore())
			bestLocation = FindBestPort(bestLocation, locations[i]);
	}

	std::cout << bestLocation.GetLocationBestDay() <<" "<< bestLocation.GetLocation();
}

void CreateWeatherReport(Weather locations[])
{
	std::fstream outputFile;
	outputFile.open("LaunchAnalysisReport.csv", std::ios::out | std::ios::app);
	outputFile << "Location:" << ", " << "Date:" << "\n";
	for (unsigned i = 0; i < 4; i++) {
		outputFile << locations[i].GetLocation() << ", " << locations[i].GetLocationBestDay() << "\n";
	}

	outputFile.close();
}

void ReadFromFile(std::ifstream& file,
	std::string& line,
	std::string& word,
	Weather locations[],
	Weather& weather,
	int temperatureMin = 1,
	int temperatureMax = 32,
	std::string firstClouds = "Cumulus",
	std::string secondClouds = "Nimbus")
{
	unsigned wordCounter = 0;
	bool isValid = 0;
	while (std::getline(file, line))
	{
		std::stringstream s(line);
		std::string rowName = "";
		wordCounter = 0;
		while (std::getline(s, word, ',')) {

			if (word == "Day/Parameter")
				break;

			if (rowName == "")
			{
				rowName = word;
			}
			else
			{
				wordCounter++;
				isValid = weather.GetDay(wordCounter);
				if (rowName == "Temperature (C)")
					weather.CheckTemperature(word, wordCounter, temperatureMin, temperatureMax);
				else if (rowName == "Wind (m/s)")
					weather.CheckWind(word, wordCounter, isValid);
				else if (rowName == "Humidity (%)")
					weather.CheckHumidity(word, wordCounter, isValid);
				else if (rowName == "Precipitation (%)")
					weather.CheckPrecipitation(word, wordCounter, isValid);
				else if (rowName == "Lightning")
					weather.CheckLightning(word, wordCounter, isValid);
				else if (rowName == "Clouds")
					weather.CheckClouds(word, wordCounter, isValid, firstClouds, secondClouds);
			}
		}
	}
}

void OpenFile(std::string folderName, std::string locationName, Weather locations[])
{
	Weather weather;
	std::string fileName = folderName + locationName;
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Failed to open the file.\n";
		return;
	}

	size_t pos = locationName.find(".csv");
	if (pos != std::string::npos)
	{
		locationName.erase(pos, 4);
	}

	weather.SetLocation(locationName);

	int input = 0;
	std::cout << "Would you like to input parameters for the weather criteria " <<"for "<< locationName <<"?\n"<< "/* 0 for No and 1 for Yes */\n";
	std::cin >> input;
	if (input != 0 && input != 1) {
		std::cout<< "Invalid input. Please enter 0 or 1.\n";
		return;
	}

	std::string line;
	std::string word;
	if (input != 1)
	{
		ReadFromFile(file, line, word, locations, weather);
	}
	else
	{
		int temperatureMin, temperatureMax = 0;
		std::string firstClouds, secondClouds;
		std::cout << "Please input min temperature: ";
		std::cin >> temperatureMin;
		std::cout << "Please input max temperature: ";
		std::cin >> temperatureMax;
		std::cout << "Please input one type of clouds which aren't allowed: ";
		std::cin >> firstClouds;
		std::cout << "Please input another type of clouds which aren't allowed: ";
		std::cin >> secondClouds;

		ReadFromFile(file, line, word, locations, weather, temperatureMin, temperatureMax, firstClouds, secondClouds);
	}
	
	locations[fileNumber] = weather;
	fileNumber++;

	file.close();
}

int main()
{
	std::string folderName;
	std::cout << "Welcome to SPACE mission control centre\n";
	std::cout << "Please enter a folder path: ";
	std::cin >> folderName; // "D:\\trying\\ Kourou.csv"
	
	Weather locations[4];

	std::string Kourou="Kourou.csv";
	std::string Tanegashima = "Tanegashima.csv";
	std::string CapeCanaveral = "CapeCanaveral.csv";
	std::string Kodiak = "Kodiak.csv";

	OpenFile(folderName, Kourou, locations);
	OpenFile(folderName, Tanegashima, locations);
	OpenFile(folderName, CapeCanaveral, locations);
	OpenFile(folderName, Kodiak, locations);

	CreateWeatherReport(locations);
	GetBestDay(locations);

	std::string senderEmail, receiverEmail, password;
	std::cout << "Please enter a sender email: ";
	std::cin >> senderEmail;
	std::cout << "Please enter a receiver email: ";
	std::cin >> receiverEmail;
	std::cout << "Please enter a password: ";
	std::cin >> password;
}
