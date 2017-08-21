// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x4a;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xa2;
        pchMessageStart[3] = 0x32;
        nDefaultPort = 26855;
        nRPCPort = 25855;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 18);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.

        const char* pszTimestamp = "Altcommunitycoin is Born - Bitcoin Block #480805 000000000000000000cd10294e773d30905e853000c99165300b3539f2fc6454 ";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1502959847, vin, vout, 0); 
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1502959847; 
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 9368;

               hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00003d1ca1e05ec4f789fd88e533796c14ee47c1906e189ec6e6be48096defb5"));
        assert(genesis.hashMerkleRoot == uint256("0x94a6d2d3723d2b037be63b9671b7e6c8bf799e6b8fe653508113b45cadfebd94"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,67);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,64);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x50)(0xE7)(0xFC)(0x0A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x50)(0x9E)(0x4)(0x2F).convert_to_container<std::vector<unsigned char> >();

        // altcommunitycoin dns seeds
          vSeeds.push_back(CDNSSeedData("seed1",  "109.230.231.36"));
          vSeeds.push_back(CDNSSeedData("seed2",  "109.230.231.53"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 0x7fffffff;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x54;
        pchMessageStart[1] = 0xac;
        pchMessageStart[2] = 0xb3;
        pchMessageStart[3] = 0xaa;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        nDefaultPort = 36855;
        nRPCPort = 35855;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1502959847;
        genesis.nNonce = 294432;
     
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00006f1f66a0871c12a59cf54918ed470a211fa4e85cfed137a4dd97245503a3"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,102);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x1D)(0x9B)(0x7F)(0x74).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x1D)(0xC0)(0xFC)(0x28).convert_to_container<std::vector<unsigned char> >();

        // altcommunitycoin dns seeds
        // vSeeds.push_back(CDNSSeedData("Seed",  "0.0.0.0"));

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc2;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0x24;
        pchMessageStart[3] = 0xab;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1502959847; 
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 5;
        nDefaultPort = 37855;
        strDataDir = "regtest";

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x38e8233fb0c983a91b34575d581c69e09af071feab0abb5fc32a5a87912e4b60"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
