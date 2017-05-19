//===- chainMaker.cpp ----------------------------------------------------*- C++ -*-===//
//
//  Copyright (C) 2017  Mario Barbareschi (mario.barbareschi@unina.it)
//
//  This file is part of PHEMAP.
//
//  PHEMAP is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  PHEMAP is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with PHEMAP. If not, see <https://www.gnu.org/licenses/agpl-3.0.html>.
//
//===----------------------------------------------------------------------===//
/// \file chainMaker.cpp
/// \author Mario Barbareschi
/// \brief This file defines the main function for generating chains
//===----------------------------------------------------------------------===//

extern "C"{
#include "utils.h"
}

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <array>
#include <vector>
#include <cstring>
#include "dummyPuf.h"

typedef std::array<puf_t, 16> pufArray;

struct PufHasher {
    std::size_t operator()(const pufArray& a) const{
        std::size_t h = 0;
        
        for (auto e : a) {
            h ^= std::hash<puf_t>{}(e)  + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};

std::vector<char> HexToBytes(const std::string& hex) {
    std::vector<char> bytes;
    
    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = (char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

typedef std::unordered_map<pufArray, bool, PufHasher> CRPs_t;

extern "C"{
#include "utils.h"
}

int main(int argc, char* argv[]){
    puf_t seed[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    puf_t root[16];
    phemap::DummyPuf puf = phemap::DummyPuf(&seed[0]);
    std::ofstream *chainFile;
    
    int i = 1;
    bool rootPassed = false;
    bool filePassed = false;
    
    if(argc == 2 || argc == 4 || argc > 5){
        std::cout << "USAGE: chainMaker [-r <root>] [-f <file>]" << std::endl;
    } else{
        while (i + 1 < argc){ // Check that we haven't finished parsing already
            if (0 == strncmp(argv[i], "-r", 2)) {
                std::vector<char> rootBytes = HexToBytes(std::string(argv[i+1]));
                memcpy(root, rootBytes.data(), 16);
                rootPassed = true;
            } else if (0 == strncmp(argv[i], "-f", 2)) {
                chainFile = new std::ofstream(std::string(argv[i+1]));
                if(!chainFile->is_open()){
                    std::cerr << "Cannot open the file "<< argv[i+1] << std::endl;
                } else {
                    std::cout << "Chain will be written onto "<< argv[i+1] << std::endl;
                    filePassed = true;
                }
            }
            i+=2;
        }
    }
    if(!rootPassed) getRandomNonce(root, 16);
    
    std::cout << "Going to generate the chain from ";
    printHexBuffer(root, 16);
    
    pufArray *challenge, *response;
    challenge = new pufArray();
    response = new pufArray();
    memcpy(challenge->data(), root, 16);
    
    CRPs_t crp;
    long long numberOfCRP = 0;
    
    while (crp.end() == crp.find(*challenge)) {
        puf.generateResponse(challenge->data(), response->data());
        crp.insert(
                   std::make_pair(*challenge, true)
                   );
        if(filePassed)
            for(int k = 0; k < 16; k++)
                *chainFile << challenge->data()[k];
        memcpy(challenge->data(), response->data(), 16);
        numberOfCRP++;
        if(0 == numberOfCRP % 10000){
            std::cout << "\rIterations: " << numberOfCRP;
            if(filePassed) chainFile->flush();
        }
    }
    std::cout << std::endl;
    std::cout << "Found collision for ";
    printHexBuffer(challenge->data(), 16);
    std::cout << " after "<< numberOfCRP << " links " << std::endl;
    
    return 0;
}
