#ifndef OOP_PNI_H
#define OOP_PNI_H

#define KHEADING 5
#define KTEMPERATURE 7
#define KDISTORTION 8
#define KCALSTATUS 9
#define KACCELX 21
#define KACCELY 22
#define KACCELZ 23
#define KPITCH 24
#define KROLL 25
#define KMAGX 27
#define KMAGY 28
#define KMAGZ 29
#define KGYROX 74
#define KGYROY 75
#define KGYROZ 76
#define KQUATERNION 77
#define KHEADINGSTATUS 79

# include <iostream>
# include <string>

class PNI_Class {
private:
	std::pair<float, bool> _kHeading;
	std::pair<float, bool> _kTemperature;
	std::pair<bool, bool> _kDistortion;
	std::pair<bool, bool> _kCalStatus;
	std::pair<float, bool> _kAccelX;
	std::pair<float, bool> _kAccelY;
	std::pair<float, bool> _kAccelZ;
	std::pair<float, bool> _kPitch;
	std::pair<float, bool> _kRoll;
	std::pair<float, bool> _kMagX;
	std::pair<float, bool> _kMagY;
	std::pair<float, bool> _kMagZ;
	std::pair<float, bool> _kGyroX;
	std::pair<float, bool> _kGyroY;
	std::pair<float, bool> _kGyroZ;
	std::pair<float[4], bool> _kQuaternion;
	std::pair<char, bool> _kHeadingStatus;
	
public:
	PNI_Class();
	~PNI_Class();

	void receive_data(void *data, unsigned int length_of_data);
	void clear();
	void headers_print() const;
};

void *convert_string_to_data(std::string &str);

#endif //OOP_PNI_H
