#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h>

// Function to convert a hexadecimal string to binary data
// This function takes a string of hexadecimal characters and converts it into a sequence of binary data.
// The binary data is stored in a vector of unsigned characters and returned.
std::vector<unsigned char> hexToBinary(const std::string& hex) {
    std::vector<unsigned char> binary;
    binary.reserve(hex.length() / 2);

    // Iterate through the hexadecimal string two characters at a time
    for (std::size_t i = 0; i < hex.length(); i += 2) {
        unsigned int byte;
        // Extract two characters from the string and convert them to an unsigned integer in hexadecimal format
        std::istringstream(hex.substr(i, 2)) >> std::hex >> byte;
        // Convert the unsigned integer to an unsigned character and store it in the binary vector
        binary.push_back(static_cast<unsigned char>(byte));
    }

    return binary;
}

int main(int argc, char* argv[]) {
    // Check if the program is provided with the correct number of command-line arguments
    // The program should be executed with the name of the input file as an argument.
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.pcapng>" << std::endl;
        return 1;
    }

    // Get the input file name from the command-line argument
    std::string input_file = argv[1];

    // Create 'certificates' directory if it does not exist
    // The program creates a directory named 'certificates' to store the output files if it doesn't already exist.
    const char* output_dir = "certificates";
    if (mkdir(output_dir, 0755) == -1) {
        // If the directory creation fails and the error is not that the directory already exists,
        // display an error message and terminate the program.
        if (errno != EEXIST) {
            std::cerr << "Error creating 'certificates' directory." << std::endl;
            return 1;
        }
    }

    // Execute tshark command and store the output in certificates.txt
    // The program runs the "tshark" command-line utility to analyze the input file for SSL handshake certificates.
    // The "-r" option specifies the input file, "-Y" filters for SSL handshake certificates,
    // "-T fields" specifies the output format as a field list, and "-e tls.handshake.certificate" specifies the certificate field.
    // The output is redirected to a file named "certificates.txt".
    std::string tshark_command = "tshark -r " + input_file + " -Y \"ssl.handshake.certificate\" -T fields -e tls.handshake.certificate > certificates.txt";
    system(tshark_command.c_str());

    // Read the certificates.txt file
    // The program opens the "certificates.txt" file to read the SSL handshake certificates extracted by tshark.
    std::ifstream infile("certificates.txt");
    std::string line;
    int counter = 1;

    // Process each line from the txt file
    // The program processes each line of the "certificates.txt" file, which contains hexadecimal strings of the certificates.
    while (std::getline(infile, line)) {
        // Convert the current line to binary DER format
        // The program uses the "hexToBinary" function to convert the hexadecimal string read from the file into binary data in DER format.
        std::vector<unsigned char> certificate_data = hexToBinary(line);

        // Write the certificate data to a binary DER file in 'certificates' directory
        // The program creates binary DER files for each certificate in the "certificates" directory.
        // The file names are in the format "certificate_<counter>.der" where <counter> is a number starting from 1.
        std::string filename = output_dir + std::string("/certificate_") + std::to_string(counter) + ".der";
        std::ofstream outfile(filename, std::ios::binary);
        outfile.write(reinterpret_cast<char*>(&certificate_data[0]), certificate_data.size());
        outfile.close();

        // Increment the counter for the next certificate
        // The program increments the counter to prepare for processing the next certificate.
        counter++;
    }

    return 0;
}
