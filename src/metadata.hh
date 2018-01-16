#ifndef METADATA_HH
#define METADATA_HH

#include "exif.hh"
#include <string>

using namespace std;

class MetaData
{
public:

    enum {
        SOFTWARE = 1,
        SIZE = (1 << 1),
        DATE = (1 << 2),
        ISO = (1 << 3),
        EXPO = (1 << 4),
        ALTITUDE = (1 << 5)
    };

    MetaData(const string &fileName, easyexif::EXIFInfo &exif);

    bool operator==(const MetaData& d);
    bool isEqual(const MetaData& d, unsigned int flag);
    string fileName() const { return fileName_; }
    void group(int g) { group_ = g; }
    int group() const { return group_; }

    friend bool compSoftware(const MetaData& a, const MetaData& b);
    friend bool compSize(const MetaData& a, const MetaData& b);
    friend bool compDate(const MetaData& a, const MetaData& b);
    friend bool compISO(const MetaData& a, const MetaData& b);
    friend bool compExpo(const MetaData& a, const MetaData& b);
    friend bool compAltitude(const MetaData& a, const MetaData& b);

    static int groupCounter;

private:
    string fileName_;
    string software_;
    long size_;
    string date_;
    int ISO_;
    double expo_;
    int altitude_;
    int group_;
};

#endif // METADATA_HH
