#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h> // For mkdir function

// Function to convert a hexadecimal string to binary data
std::vector<unsigned char> hexToBinary(const std::string& hex) {
    std::vector<unsigned char> binary;
    binary.reserve(hex.length() / 2);

    for (std::size_t i = 0; i < hex.length(); i += 2) {
        unsigned int byte;
        std::istringstream(hex.substr(i, 2)) >> std::hex >> byte;
        binary.push_back(static_cast<unsigned char>(byte));
    }

    return binary;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.pcapng>" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];

    // Create 'certificates' directory if it does not exist
    const char* output_dir = "certificates";
    if (mkdir(output_dir, 0755) == -1) {
        if (errno != EEXIST) {
            std::cerr << "Error creating 'certificates' directory." << std::endl;
            return 1;
        }
    }

    // Execute tshark command and store the output in certificates.txt
    std::string tshark_command = "tshark -r " + input_file + " -Y \"ssl.handshake.certificate\" -T fields -e tls.handshake.certificate > certificates.txt";
    system(tshark_command.c_str());

    // Read the certificates.txt file
    std::ifstream infile("certificates.txt");
    std::string line;
    int counter = 1;

    // Process each line from the txt file
    while (std::getline(infile, line)) {
        // Convert the current line to binary DER format
        std::vector<unsigned char> certificate_data = hexToBinary(line);

        // Write the certificate data to a binary DER file in 'certificates' directory
        std::string filename = output_dir + std::string("/certificate_") + std::to_string(counter) + ".der";
        std::ofstream outfile(filename, std::ios::binary);
        outfile.write(reinterpret_cast<char*>(&certificate_data[0]), certificate_data.size());
        outfile.close();

        // Increment the counter for the next certificate
        counter++;
    }

    return 0;
}
