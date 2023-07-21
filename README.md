# PcapGetCertificate

This is a C++ program designed to extract SSL certificates from pcap files. The program utilizes Wireshark for pcap packet parsing, extracts the byte stream of certificates, and then saves them as standard DER format files.



## Features

* This is a C++ program developed using the Wireshark API called "tshark" to parse pcap files without a graphical user interface (GUI).
* The program is simple yet capable of handling large pcap files efficiently. It utilizes the power of the tshark API to process and parse even large-sized pcap files without compromising performance. This enables it to handle network captures with substantial amounts of data, making it suitable for analyzing and extracting SSL certificates from extensive network traffic recordings. Its ability to manage large pcap files ensures that it can handle diverse real-world network scenarios and provide valuable insights into SSL certificate usage within complex network environments.



## Getting Started

### Test Environment

This is the Env that is used to develop this program. Different versions of the development environment may not be able to run the program.

* **TShark (Wireshark) 3.2.3 ** - found at [https://www.wireshark.org/](https://cmake.org/)
* **gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)** 


## Build and Run the project

To build the project, all you need to do, ***after correctly
[installing the project](README.md#Installing)***, is run a g++ command:

```bash
g++ get_certificates.cpp -o get_certificates
./get_certificates SSL.pcappng
```

> ***Note:*** *SSL.pcappng is the pcap file that you want to work on*.

## Resulting Certificates

After the program finishes running, all the certificates obtained will be saved in DER format within the "./certificates" folder.

## Contributing

Not available now

## Versioning

Not available now

## Authors

* **Leiber Baoqian LYU** - [@Leiber](https://github.com/Leiber-CivilComEngineer)

## License

Not available now

## References

- https://www.wireshark.org/docs/dfref/t/tls.html
- https://www.wireshark.org/docs/wsdg_html/
- https://www.wireshark.org/docs/
- https://richardatkin.com/post/2022/01/15/Identifying-and-retrieving-certificates-from-a-PCAP-file-using-Wireshark.html
- https://blog.csdn.net/u014786330/article/details/88399498
- https://www.cnblogs.com/bonelee/p/13522166.html
- https://osqa-ask.wireshark.org/questions/41034/extract-certificate-info-with-tshark/
- https://serverfault.com/questions/313610/extracting-ssl-certificates-from-the-network-or-pcap-files
- https://21xrx.com/Articles/read_article/175130
- https://www.youtube.com/watch?v=-HDpYR_QSFw&list=PLW8bTPfXNGdC5Co0VnBK1yVzAwSSphzpJ&index=5
- https://www.youtube.com/watch?v=IlVppluWTHw&list=PLW8bTPfXNGdC5Co0VnBK1yVzAwSSphzpJ&index=10&pp=iAQB&themeRefresh=1
- https://www.geeksforgeeks.org/tcp-ip-model/
- https://chat.openai.com/
