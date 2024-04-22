#pragma once
#include <string>

class Weather
{
private:
    std::string location;
    bool validDays[15] = { 0 };
    int temperature[15] = { 0 };
    unsigned int windSpeed[15] = { 0 };
    unsigned int humidity[15] = { 0 };
    bool precipitation[15] = { true };
    bool lightnings[15] = { true };
    std::string clouds[15];

    unsigned bestScore = 0;

public:
    const std::string GetLocation() const { return location; };
    const bool GetDay(unsigned& loc) const { return validDays[loc - 1]; };
    const unsigned GetBestScore() const { return bestScore; };

    const unsigned GetLocationBestDay(); //gets the best day for the specific location

    void SetLocation(std::string& location);
    void SetValidDays(unsigned int& day,bool isValid );
    void SetTemperature(int& degrees, unsigned& day);
    void SetWindSpeed(unsigned int& speed, unsigned& day);
    void SetHumidity(unsigned& percent, unsigned& day);
    void SetPrecipitation(unsigned& day);
    void SetLightning(unsigned& day);
    void SetClouds(std::string& clouds, unsigned& day);

    const unsigned CountPoints(unsigned& day) const;

    void CheckTemperature(const std::string& word, unsigned counter, int temperatureMin, int temperatureMax);
    void CheckWind(const std::string& word, unsigned counter, unsigned isValid);
    void CheckHumidity(const std::string& word, unsigned counter, unsigned isValid);
    void CheckPrecipitation(const std::string& word, unsigned counter, unsigned isValid);
    void CheckClouds(const std::string& word,
        unsigned counter,
        unsigned isValid,
        std::string firstClouds,
        std::string secondClouds);
    void CheckLightning(const std::string& word, unsigned counter, unsigned isValid);
};