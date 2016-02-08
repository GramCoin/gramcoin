// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2013 The Zetacoin developers
// Copyright (c) 2014 The GramCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xc6;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0x63;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("04f09802847840aaf295de8442fbacedf5b095cdbb9bc716bd49110271b28a49e0ead8564ff0db22209e0374782c093bb899692d524e9d6a6956e7c5ecbcd68284");
        nDefaultPort = 7567;
        nRPCPort = 7566;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.

        const char* pszTimestamp = "GramCoin begins";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1429313340;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 6241844;
////////

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000009901f33bfbcf001dba13e237692c421e1e3ca43d9deb5e84cefd000cc"));
        assert(genesis.hashMerkleRoot == uint256("0x3dcfd368d2cdea92871821cb30958ad57b5b216147e715ba0872a2b22b764a20"));

        vSeeds.push_back(CDNSSeedData("node.GramCoin.org", "node.GramCoin.org"));
        vSeeds.push_back(CDNSSeedData("node.GramCoin.cf", "node.GramCoin.cf"));
        vSeeds.push_back(CDNSSeedData("GramCoin.no-ip.org", "GramCoin.no-ip.org"));

        base58Prefixes[PUBKEY_ADDRESS] = 38;
        base58Prefixes[SCRIPT_ADDRESS] = 9;
        base58Prefixes[SECRET_KEY] = 224;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time'
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
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
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0x15;
        pchMessageStart[1] = 0xfc;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0x01;
        vAlertPubKey = ParseHex("04303390343f91cc401d56d68b123028bf52e5fca1939df127f63c6467cdf9c8e2c14b61104cf817d0b780da337893ecc4aaff1309e536162dabbdb45200ca2b0a");
        nDefaultPort = 11835;
        nRPCPort = 11832;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1380747675;
        genesis.nNonce = 2091390249;


        hashGenesisBlock = genesis.GetHash();


        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();

        assert(hashGenesisBlock == uint256("0x00000c7c73d8ce604178dae13f0fc6ec0be3275614366d44b1b4b5c6e238c60c"));
		
        vFixedSeeds.clear();
        vSeeds.clear();
        // vSeeds.push_back(CDNSSeedData("GramCoin.test", "test.GramCoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = 89;
        base58Prefixes[SCRIPT_ADDRESS] = 188;
        base58Prefixes[SECRET_KEY] = 239;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
//static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x0f;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x5a;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1390748221;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 4;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 11444;
        strDataDir = "regtest";

        // debug print
        hashGenesisBlock = genesis.GetHash();
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
           if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();

        assert(hashGenesisBlock == uint256("0x57939ce0a96bf42965fee5956528a456d0edfb879b8bd699bcbb4786d27b979d"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
//static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        //case CChainParams::TESTNET:
        //    pCurrentParams = &testNetParams;
        //    break;
        //case CChainParams::REGTEST:
        //    pCurrentParams = &regTestParams;
        //    break;
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
