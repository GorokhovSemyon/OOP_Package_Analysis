#include "PNI.h"

int main() {
    std::string	package1 = "053F80000009011C40000000";
    std::string	package2 = "4C41A400004B3F91BCD8";
    std::string package3 = "0741A40000053F91BCD819413547AE";
    std::string	package4 = "05430D083B183F91BCD8193EDF4DE94D422869E241F8F5C341DEC28F3C594D0E";
    std::string	package5 = "05430D083B183F91BCD8193EDF4DE94F00080015BCA408C0163BFB4DAB173F80F5081BC16EA4371CC12D31271D42513D4F4A000000004B000000004C00000000";
    PNI_Class receiver;
    void *data;

    std::cout << "1-st test" << std::endl;
    data = convert_string_to_data(package1);
    receiver.receive_data(data, package1.length() / 2);
    receiver.headers_print();
    receiver.clear();
    delete[] static_cast < unsigned char *>(data);

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    std::cout << "2-nd test" << std::endl;
    data = convert_string_to_data(package2);
    receiver.receive_data(data, package2.length() / 2);
    receiver.headers_print();
    receiver.clear();
    delete[] static_cast<unsigned char *>(data);

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    std::cout << "3-rd test" << std::endl;
    data = convert_string_to_data(package3);
    receiver.receive_data(data, package3.length() / 2);
    receiver.headers_print();
    receiver.clear();
    delete[] static_cast<unsigned char *>(data);

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    std::cout << "4-th test" << std::endl;
    data = convert_string_to_data(package4);
    receiver.receive_data(data, package4.length() / 2);
    receiver.headers_print();
    receiver.clear();
    delete[] static_cast<unsigned char *>(data);

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    std::cout << "5-th test" << std::endl;
    data = convert_string_to_data(package5);
    receiver.receive_data(data, package5.length() / 2);
    receiver.headers_print();
    receiver.clear();
    delete[] static_cast<unsigned char *>(data);

    return 0;
}
