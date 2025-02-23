#include <bitset>
#include <iostream>
#include <string>

using namespace std;

// Function to calculate checksum with 1's complement
string calculateChecksum(const string &binaryString, int chunkSize) {
  int sum = 0;
  int length = binaryString.length();

  // Process the binary string in chunks
  for (size_t i = 0; i < length; i += chunkSize) {
    // Extract a chunk of the specified size
    string chunk = binaryString.substr(i, chunkSize);

    // Convert the chunk to an integer
    bitset<8> bits(chunk);  // Use 8 bits to handle both 4-bit and 8-bit chunks
    sum += bits.to_ulong(); // Add the chunk value to the sum
  }

  // Take the 1's complement of the sum
  int mask = (1 << chunkSize) - 1; // Create a mask for the chunk size
  sum = ~sum;                      // Take the 1's complement
  sum = sum & mask;                // Truncate to the chunk size

  // Convert the sum to a binary string of the correct size
  bitset<8> checksumBits(
      sum); // Use 8 bits to handle both 4-bit and 8-bit chunks
  return checksumBits.to_string().substr(
      8 - chunkSize); // Return only the relevant bits
}

int main() {
  string binaryString;

  // Input binary data
  cout << "Enter your binary data: ";
  cin >> binaryString;

  // Determine chunk size based on input length
  int chunkSize = (binaryString.length() >= 24) ? 8 : 4;

  // Calculate checksum
  string checksum = calculateChecksum(binaryString, chunkSize);

  // Output the checksum
  cout << "Checksum: " << checksum << endl;

  return 0;
}
/**
Input:
Enter your binary data: 1101011101110111010111011
Checksum: 01010011

Enter your binary data: 11010111
Checksum: 1011
*/