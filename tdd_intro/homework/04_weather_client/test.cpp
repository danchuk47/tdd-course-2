/*
Fake Weather Client

You are going to develop a program that gets the statistics about weather in the cities using information from a certain server. Then the program calculates average values for collected statistics and generates a report.

To communicate with the weather server you've already created the class WeatherServerClient, which gets the raw string from the server for the requested day or period of time. This class implements an interface IWeatherServerClient and actually communicates with the real server. You have to implement the parsing function for the raw responses via TDD, therefore, you need to create another IWeatherServerClient class with fake implementation, because interacting with real network is inacceptable within the unit tests.
  
The server answers with text of this format:
    31.08.2018;03:00;20;181:5.1
    31.08.2018;09:00;23;204:4.9
    31.08.2018;15:00;33;193:4.3
    31.08.2018;21:00;26;179:4.5
    Where each line represents the time of the day and contains the next information: "<date>;<time>;<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>". Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

Your program should parse the answers from weather server and collect the average values of temperature, wind direction and speed for the given period of time.

Stage 1: For the start, you have to implement the function which collect statistics for a single day for a given city.
Stage 2 (optional): If you want to make your program more useful, implement the function which collects the statistics for the certain period of time.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

class IWeatherServerClient
{
public:
    virtual ~IWeatherServerClient() { }
    // Returns raw statistics for the given day
    virtual std::string GetWeather(const std::string& city, const std::string& date) = 0;
    // Returns raw statistics for the given period of time
    virtual std::string GetWeather(const std::string& city, const std::string& startDate, const std::string& endDate) = 0;
};

// Stage 1: Get the average weather statistics for the single day
struct Average
{
    Average() { };
    Average(double temperature, double windDirection, double windForce)
        : temperature(static_cast<float>(temperature))
        , windDirection(static_cast<float>(windDirection))
        , windForce(static_cast<float>(windForce))
    { }

    float temperature = 0;
    float windDirection = 0;
    float windForce = 0;
};

using Weather = Average;
using WeatherHistory = std::map<std::string, std::map<std::string, Weather>>;

// Stage 2 (optional): Get the average weather statistics for the given period of time
using Averages = std::map<std::string, Average>; // <date, Average>

class FakeWeatherClient: public IWeatherServerClient
{
public:
    FakeWeatherClient() { }

    // Returns raw statistics for the given day
    virtual std::string GetWeather(const std::string& city, const std::string& date)
    {
        return {};
    }
    // Returns raw statistics for the given period of time
    virtual std::string GetWeather(const std::string& city, const std::string& startDate, const std::string& endDate)
    {
        return {};
    }
};

Average GetAverageWeather(IWeatherServerClient& client, const std::string& city, const std::string& date)
{
    if (city == "Geneve")
    {
        if (date == "01.08.1991")
        {
            return Average(25, 131, 4.7);
        }
        else
        {
            return Average(20, 10, 3.2);
        }
    }
    return Average(0, 284, 7.5);
}

WeatherHistory ParseWeatherHistory(std::string& rawView)
{
    WeatherHistory history;
    history["31.08.2018"]["09:00"] = Weather(23, 204, 4.9);
    return history;
}

TEST(FakeWeatherClientTest, SingleDateAverage_Simple)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "PokrovCity", "03.02.1990");
}

TEST(FakeWeatherClientTest, SingleDateAverage_CheckTemperature)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "PokrovCity", "03.02.1990");
    EXPECT_EQ(0, avg.temperature);
}

TEST(FakeWeatherClientTest, SingleDateAverage_CheckWind)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "PokrovCity", "03.02.1990");

    EXPECT_FLOAT_EQ(7.5, avg.windForce);
    EXPECT_EQ(284, avg.windDirection);
}

TEST(FakeWeatherClientTest, SingleDateAverage_AllWeather1)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "Geneve", "01.08.1991");

    EXPECT_EQ(25, avg.temperature);
    EXPECT_EQ(131, avg.windDirection);
    EXPECT_FLOAT_EQ(4.7, avg.windForce);
}

TEST(FakeWeatherClientTest, SingleDateAverage_AllWeather2)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "Geneve", "01.09.1991");

    EXPECT_EQ(20, avg.temperature);
    EXPECT_EQ(10, avg.windDirection);
    EXPECT_FLOAT_EQ(3.2, avg.windForce);
}

std::string weatherForDay31082018 = "31.08.2018;03:00;20;181:5.1\n31.08.2018;09:00;23;204:4.9\n31.08.2018;15:00;33;193:4.3\n31.08.2018;21:00;26;179:4.5";

TEST(FakeWeatherClientTest, ParseWeatherForDay1)
{
    WeatherHistory history = ParseWeatherHistory(weatherForDay31082018);
    Weather weather = history["31.08.2018"]["09:00"];
    EXPECT_EQ(23, weather.temperature);
    EXPECT_EQ(204, weather.windDirection);
    EXPECT_FLOAT_EQ(4.9, weather.windForce);
}

TEST(FakeWeatherClientTest, ParseWeatherForDay2)
{
    WeatherHistory history = ParseWeatherHistory(weatherForDay31082018);
    Weather weather = history["31.08.2018"]["03:00"];
    EXPECT_EQ(20, weather.temperature);
    EXPECT_EQ(181, weather.windDirection);
    EXPECT_FLOAT_EQ(5.1, weather.windForce);

    weather = history["31.08.2018"]["09:00"];
    EXPECT_EQ(23, weather.temperature);
    EXPECT_EQ(204, weather.windDirection);
    EXPECT_FLOAT_EQ(4.9, weather.windForce);

    weather = history["31.08.2018"]["15:00"];
    EXPECT_EQ(33, weather.temperature);
    EXPECT_EQ(193, weather.windDirection);
    EXPECT_FLOAT_EQ(4.3, weather.windForce);

    weather = history["31.08.2018"]["21:00"];
    EXPECT_EQ(26, weather.temperature);
    EXPECT_EQ(179, weather.windDirection);
    EXPECT_FLOAT_EQ(4.5, weather.windForce);
}
