#include "Weather.h"

const unsigned Weather::GetLocationBestDay()
{
	unsigned currentScore = 0;
	unsigned bestDay = 0;
	unsigned bestScore = 0;
	for (unsigned i = 0; i < 15; i++)
	{
		if (validDays[i] == 1)
		{
			bestScore = CountPoints(i);
			if (currentScore < bestScore)
			{
				currentScore = bestScore;
				bestDay = i + 1;
			}
		}
	}
	this->bestScore = bestScore;
	return bestDay;
}

void Weather::SetLocation(std::string& location)
{
	this->location = location;
}

void Weather::SetValidDays(unsigned int& day, bool isValid)
{
	validDays[day - 1] = isValid;
}

void Weather::SetTemperature( int& degrees, unsigned & day)
{
	temperature[day - 1] = degrees;
}

void Weather::SetWindSpeed(unsigned int& speed, unsigned& day)
{
	windSpeed[day - 1] = speed;
}

void Weather::SetHumidity(unsigned& percent, unsigned& day)
{
	humidity[day - 1] = percent;
}

void Weather::SetPrecipitation(unsigned& day)
{
	precipitation[day - 1] = false;
}

void Weather::SetLightning(unsigned& day)
{
	lightnings[day - 1] = false;
}

void Weather::SetClouds(std::string& clouds, unsigned& day)
{
	this->clouds[day - 1] = clouds;
}

const unsigned Weather::CountPoints(unsigned& day) const 
{
	//each point of wind speed equals 5 points of humidity
	return windSpeed[day] * 5 + humidity[day]; 
}

void Weather::CheckTemperature(const std::string& word, unsigned counter, int temperatureMin, int temperatureMax) {

	int degrees = std::stoi(word);
	if (degrees > temperatureMin && degrees < temperatureMax) {
		SetTemperature(degrees, counter);
		SetValidDays(counter, true);
	}
	else {
		SetValidDays(counter, false);
	}
}

void Weather::CheckWind(const std::string& word, unsigned counter, unsigned isValid)
{
	if (!isValid)
		return;

	unsigned maxSpeed = 11;
	unsigned windSpeed = std::stoi(word);
	if (windSpeed <= maxSpeed)
		SetWindSpeed(windSpeed, counter);
	else
		SetValidDays(counter, false);
}

void Weather::CheckHumidity(const std::string& word,  unsigned counter, unsigned isValid) {

	if (!isValid)
		return;

	unsigned percent = std::stoi(word);
	unsigned maxPercent = 55;
	if (percent < maxPercent)
		SetHumidity(percent, counter);
	else
		SetValidDays(counter, false);
}

void Weather::CheckPrecipitation(const std::string& word, unsigned counter, unsigned isValid) {

	if (!isValid)
		return;

	unsigned percent = std::stoi(word);
	if (percent == 0)
		SetPrecipitation(counter);
	else
		SetValidDays(counter, false);
}

void Weather::CheckClouds(const std::string& word, 
	unsigned counter,
	unsigned isValid,
	std::string firstClouds,
	std::string secondClouds) 
{
	if (!isValid)
		return;

	if (word != firstClouds && word != secondClouds)
	{
		std::string clouds = word;
		SetClouds(clouds, counter);
	}
	else
		SetValidDays(counter, false);
}

void Weather::CheckLightning(const std::string& word, unsigned counter, unsigned isValid)
{
	if (!isValid)
		return;
	
	if (word == "No")
		SetLightning(counter);
	else
		SetValidDays(counter, false);
}