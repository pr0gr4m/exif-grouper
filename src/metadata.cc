#include "metadata.hh"
#include <string>
#include <cmath>
#include <ctgmath>

using namespace std;

int MetaData::groupCounter = 1;

MetaData::MetaData(const string &fileName, easyexif::EXIFInfo &exif)
    : fileName_(fileName),
      software_(exif.Software),
      size_((long)(log10(exif.ImageWidth + exif.ImageHeight))),
      date_(exif.DateTime.substr(0, 10)),
      ISO_(exif.ISOSpeedRatings),
      expo_(exif.ExposureTime),
      altitude_((int)(exif.GeoLocation.Altitude / 5)),
      group_(0)
{
}

bool MetaData::operator ==(const MetaData& d)
{
    return (software_ == d.software_ &&
            size_ == d.size_ &&
            date_ == d.date_ &&
            ISO_ == d.ISO_ &&
            expo_ == d.expo_ &&
            altitude_ == d.altitude_);
}

bool MetaData::isEqual(const MetaData& d, unsigned int flag)
{
    if (flag & SOFTWARE)
        if (!(software_ == d.software_))
            return false;
    if (flag & SIZE)
        if (!(size_ == d.size_))
            return false;
    if (flag & DATE)
        if (!(date_ == d.date_))
            return false;
    if (flag & ISO)
        if (!(ISO_ == d.ISO_))
            return false;
    if (flag & EXPO)
        if (!(expo_ == d.expo_))
            return false;
    if (flag & ALTITUDE)
        if (!(altitude_ == d.altitude_))
            return false;
    return true;
}

bool compSoftware(const MetaData& a, const MetaData& b)
{
    return a.software_ < b.software_;
}

bool compSize(const MetaData& a, const MetaData& b)
{
    return a.size_ < b.size_;
}

bool compDate(const MetaData& a, const MetaData& b)
{
    return a.date_ < b.date_;
}

bool compISO(const MetaData& a, const MetaData& b)
{
    return a.ISO_ < b.ISO_;
}

bool compExpo(const MetaData& a, const MetaData& b)
{
    return a.expo_ < b.expo_;
}

bool compAltitude(const MetaData& a, const MetaData& b)
{
    return a.altitude_ < b.altitude_;
}
