#include "PNI.h"

PNI_Class::PNI_Class() {
    this->clear();
}


PNI_Class::~PNI_Class() {
    this->clear();
}

void PNI_Class::clear() {
    this->_kHeading.second = false;
    this->_kPitch.second = false;
    this->_kRoll.second = false;
    this->_kHeadingStatus.second = false;
    this->_kQuaternion.second = false;
    this->_kTemperature.second = false;
    this->_kDistortion.second = false;
    this->_kCalStatus.second = false;
    this->_kAccelX.second = false;
    this->_kAccelY.second = false;
    this->_kAccelZ.second = false;
    this->_kMagX.second = false;
    this->_kMagY.second = false;
    this->_kMagZ.second = false;
    this->_kGyroX.second = false;
    this->_kGyroY.second = false;
    this->_kGyroZ.second = false;
}

unsigned char convert_hex_to_dec(const unsigned char array[2]) {
	unsigned char id;
	id = 0;
	if (array[0] - '0' < 10) {
		id += (array[0] - '0') * 16;
	} else {
		switch (array[0]) {
			case 'A':
				id += 10 * 16;
				break;
			case 'B':
				id += 11 * 16;
				break;
			case 'C':
				id += 12 * 16;
				break;
			case 'D':
				id += 13 * 16;
				break;
			case 'E':
				id += 14 * 16;
				break;
			case 'F':
				id += 15 * 16;
		}
	}
	if (array[1] - '0' < 10) {
		id += (array[1] - '0');
	}
	else {
		switch (array[1]) {
			case 'A':
				id += 10;
				break;
			case 'B':
				id += 11;
				break;
			case 'C':
				id += 12;
				break;
			case 'D':
				id += 13;
				break;
			case 'E':
				id += 14;
				break;
			case 'F':
				id += 15;
		}
	}

	return id;
}

void *convert_string_to_data(std::string &str) {
    int i = 0;
    int j = 0;
    void *data;
    unsigned char *array;
    unsigned char byte[2];

    array = new unsigned char [str.length() / 2];
    while (i < str.length()) {
        byte[0] = str[i++];
        byte[1] = str[i++];
        array[j++] = convert_hex_to_dec(byte);
    }
    data = static_cast<void *>(array);

    return data;
}

void BigEndian_to_LittleEndian_float(unsigned char* BE_ptr, const unsigned char* data_ptr, int* cnt) {
    for (int j = 3; j >= 0; j--) {
        BE_ptr[j] = data_ptr[(*cnt)++];
    }
}

void BigEndian_to_LittleEndian_bool(unsigned char* BE_ptr) {
    for (int i = 3; i >= 0; i--) {
        BE_ptr[i] = 0;
    }
}

void PNI_Class::headers_print() const {
    std::cout.precision(8);
    if (this->_kHeading.second)
		std::cout << "kHeading = " << this->_kHeading.first << std::endl;
	if (this->_kPitch.second)
		std::cout << "kPitch = " << this->_kPitch.first << std::endl;
	if (this->_kRoll.second)
		std::cout << "kRoll = " << this->_kRoll.first << std::endl;
	if (this->_kHeadingStatus.second)
        std::cout << "kHeadingStatus = " << (int)this->_kHeadingStatus.first << std::endl;
	if (this->_kQuaternion.second) {
		std::cout << "kQuaternion: [" << this->_kQuaternion.first[0];
		std::cout << ", " << this->_kQuaternion.first[1];
		std::cout << ", " << this->_kQuaternion.first[2];
		std::cout << ", " << this->_kQuaternion.first[3] << "]" << std::endl;
	}
	if (this->_kTemperature.second)
		std::cout << "kTemperature = " << this->_kTemperature.first << std::endl;
	if (this->_kDistortion.second)
        if (this->_kDistortion.first)
            std::cout << "kDistortion = true" << std::endl;
        else
            std::cout << "kDistortion = false" << std::endl;
	if (this->_kCalStatus.second)
        if (this->_kCalStatus.first)
            std::cout << "kCalStatus = true" << std::endl;
        else
            std::cout << "kCalStatus = false" << std::endl;
	if (this->_kAccelX.second)
		std::cout << "kAccelX = " << this->_kAccelX.first << std::endl;
	if (this->_kAccelY.second)
		std::cout << "kAccelY = " << this->_kAccelY.first << std::endl;
	if (this->_kAccelZ.second)
		std::cout << "kAccelZ = " << this->_kAccelZ.first << std::endl;
	if (this->_kMagX.second)
		std::cout << "kMagX = " << this->_kMagX.first << std::endl;
	if (this->_kMagY.second)
		std::cout << "kMagY = " << this->_kMagY.first << std::endl;
	if (this->_kMagZ.second)
		std::cout << "kMagZ = " << this->_kMagZ.first << std::endl;
	if (this->_kGyroX.second)
		std::cout << "kGyroX = " << this->_kGyroX.first << std::endl;
	if (this->_kGyroY.second)
		std::cout << "kGyroY = " << this->_kGyroY.first << std::endl;
	if (this->_kGyroZ.second)
		std::cout << "kGyroZ = " << this->_kGyroZ.first << std::endl;
}

void PNI_Class::receive_data(void *data, unsigned int length_of_data) {
    int i = 0;
    unsigned char id;
    unsigned char *ptr_to_data;
    unsigned char tmp[4] = {0, 0, 0, 0};

    ptr_to_data = static_cast<unsigned char *>(data);

    while (i < length_of_data) {
        id = ptr_to_data[i++];
        switch (id) {
            case KHEADING:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kHeading.first = *reinterpret_cast<float *>(tmp);
                this->_kHeading.second = true;
                break;
            case KTEMPERATURE:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kTemperature.first = *reinterpret_cast<float *>(tmp);
                this->_kTemperature.second = true;
                break;
            case KDISTORTION:
                BigEndian_to_LittleEndian_bool(tmp);
                tmp[0] = ptr_to_data[i++];
                this->_kDistortion.first = *reinterpret_cast<bool *>(tmp);
                this->_kDistortion.second = true;
                break;
            case KCALSTATUS:
                BigEndian_to_LittleEndian_bool(tmp);
                tmp[0] = ptr_to_data[i++];
                this->_kCalStatus.first = *reinterpret_cast<bool *>(tmp);
                this->_kCalStatus.second = true;
                break;
            case KACCELX:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kAccelX.first = *reinterpret_cast<float *>(tmp);
                this->_kAccelX.second = true;
                break;
            case KACCELY:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kAccelY.first = *reinterpret_cast<float *>(tmp);
                this->_kAccelY.second = true;
                break;
            case KACCELZ:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kAccelZ.first = *reinterpret_cast<float *>(tmp);
                this->_kAccelZ.second = true;
                break;
            case KPITCH:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kPitch.first = *reinterpret_cast<float *>(tmp);
                this->_kPitch.second = true;
                break;
            case KROLL:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kRoll.first = *reinterpret_cast<float *>(tmp);
                this->_kRoll.second = true;
                break;
            case KMAGX:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kMagX.first = *reinterpret_cast<float *>(tmp);
                this->_kMagX.second = true;
                break;
            case KMAGY:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kMagY.first = *reinterpret_cast<float *>(tmp);
                this->_kMagY.second = true;
                break;
            case KMAGZ:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kMagZ.first = *reinterpret_cast<float *>(tmp);
                this->_kMagZ.second = true;
                break;
            case KGYROX:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kGyroX.first = *reinterpret_cast<float *>(tmp);
                this->_kGyroX.second = true;
                break;
            case KGYROY:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kGyroY.first = *reinterpret_cast<float *>(tmp);
                this->_kGyroY.second = true;
                break;
            case KGYROZ:
                BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                this->_kGyroZ.first = *reinterpret_cast<float *>(tmp);
                this->_kGyroZ.second = true;
                break;
            case KQUATERNION:
                for (float & j : this->_kQuaternion.first) {
                    BigEndian_to_LittleEndian_float(tmp, ptr_to_data, &i);
                    j = *reinterpret_cast<float *>(tmp);
                    this->_kQuaternion.second = true;
                }
                break;
            case KHEADINGSTATUS:
                BigEndian_to_LittleEndian_bool(tmp);
                tmp[0] = ptr_to_data[i++];
                this->_kHeadingStatus.first = *reinterpret_cast<char *>(tmp);
                this->_kHeadingStatus.second = true;
                break;
            default:
                break;
        }
    }
}