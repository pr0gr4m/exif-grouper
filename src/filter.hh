#ifndef FILTER_HH
#define FILTER_HH

#include "exif.hh"
#include <string>

constexpr double LATITUDEMIN = -90;
constexpr double LATITUDEMAX = 90;
constexpr double LONGTITUDEMIN = -180;
constexpr double LONGTITUDEMAX = 180;
const std::string VENDORANY = "/";
const std::string MODELANY = "/";
constexpr unsigned WIDTHMIN = 0;
constexpr unsigned WIDTHMAX = 65535;
constexpr unsigned HEIGHTMIN = 0;
constexpr unsigned HEIGHTMAX = 65535;
const std::string DATEMIN = "1970:01:01";
const std::string DATEMAX = "2100:01:01";
const std::string TIMEMIN = "00:00:00";
const std::string TIMEMAX = "23:59:59";

class Filter
{
public:

    void latitudeMin(double latitude) { latitudeMin_ = latitude; }
    double latitudeMin() { return latitudeMin_; }
    void latitudeMax(double latitude) { latitudeMax_ = latitude; }
    double latitudeMax() { return latitudeMax_; }

    void longtitudeMin(double longtitude) { longtitudeMin_ = longtitude; }
    double longtitudeMin() { return longtitudeMin_; }
    void longtitudeMax(double longtitude) { longtitudeMax_ = longtitude; }
    double longtitudeMax() { return longtitudeMax_; }

    void vendor(std::string v) { vendor_ = v; }
    std::string vendor() { return vendor_; }

    void model(std::string m) { model_ = m; }
    std::string model() { return model_; }

    void dateMin(std::string date) { dateMin_ = date; }
    std::string dateMin() { return dateMin_; }
    void dateMax(std::string date) { dateMax_ = date; }
    std::string dateMax() { return dateMax_; }

    void timeMin(std::string t) { timeMin_ = t; }
    std::string timeMin() { return timeMin_; }
    void timeMax(std::string t) { timeMax_ = t; }
    std::string timeMax() { return timeMax_; }

    bool setFilter(std::string latitudeMin, std::string latitudeMax,
                   std::string longtitudeMin, std::string longtitudeMax,
                   std::string v, std::string m,
                   std::string widthMin, std::string widthMax,
                   std::string heightMin, std::string heightMax,
                   std::string dateMin, std::string dateMax,
                   std::string timeMin, std::string timeMax);

    bool cmpFilter(easyexif::EXIFInfo& info);

public:
    static Filter *getInstance();

private:
    Filter();
    virtual ~Filter() { instanceFlag = false; }
    static bool instanceFlag;
    static Filter *instance;

private:
    double latitudeMin_;
    double latitudeMax_;
    double longtitudeMin_;
    double longtitudeMax_;
    std::string vendor_;
    std::string model_;
    unsigned widthMin_;
    unsigned widthMax_;
    unsigned heightMin_;
    unsigned heightMax_;
    std::string dateMin_;
    std::string dateMax_;
    std::string timeMin_;
    std::string timeMax_;
};

#endif // FILTER_HH
