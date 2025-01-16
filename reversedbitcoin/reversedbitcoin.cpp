/**
  ____                                                  _   ____    _   _                    _         
 |  _ \    ___  __   __   ___   _ __   ___    ___    __| | | __ )  (_) | |_    ___    ___   (_)  _ __  
 | |_) |  / _ \ \ \ / /  / _ \ | '__| / __|  / _ \  / _` | |  _ \  | | | __|  / __|  / _ \  | | | '_ \ 
 |  _ <  |  __/  \ V /  |  __/ | |    \__ \ |  __/ | (_| | | |_) | | | | |_  | (__  | (_) | | | | | | |
 |_| \_\  \___|   \_/    \___| |_|    |___/  \___|  \__,_| |____/  |_|  \__|  \___|  \___/  |_| |_| |_| 
                                                                                             
*/


// Copyright (c) 2010 Satoshi Nakamoto
// The Bitcoin Core Developers 2009-2023
// ReversedBitcoin Developers 2023-2023
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <reversedbitcoin.h>

#include <reversedbitcoinseeds.h>
#include <consensus/merkle.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>


#include "uint256.h"
#include "arith_uint256.h"
#include "hash.h"
#include "streams.h"
#include <time.h>



static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


static CBlock CreateGenesisBlockMainNet(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "The time machine";
    const CScript genesisOutputScript = CScript() << ParseHex("0485b14d22ad3bf0c3e2957504e7a052ea3ba2c01ca9966241f8f691d3abc6b2790750158b7cd3d02796f14a22b60d0ddbd81a7380662b98cdb9a779c61786cd37") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

static CBlock CreateGenesisBlockTestNet(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "The time machine";
    const CScript genesisOutputScript = CScript() << ParseHex("0479f35706a6d0db91d61d9d4116ab2f38340f4c38897cda17c9bab9c72d28f6434931ad2cf280dc7508b912ace1ea255b5f37db598bcc7d62431476f5d861510d") << OP_CHECKSIG;
//    const CScript genesisOutputScript = CScript() << ParseHex("04b9106474eae57736be77d6e22b6bb76d4325bddde7d1980b8c67bbf3f6b3890e446c7ae5aecfbecf988fa85b13fe4688b79e0989d21c0313f69f21e8265a1d88") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

static CBlock CreateGenesisBlockRegTest(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "The time machine";
    const CScript genesisOutputScript = CScript() << ParseHex("04e8d29d3dab961e3242baef836325163bc502381c4f89e87ef64153b17a32d57275149b4cd2ff6d36e2d83e4fc3d802432d84d44b5c5e514da5fd7e62ee83fa9e") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}


/**
'##::::'##::::'###::::'####:'##::: ##:'##::: ##:'########:'########:
 ###::'###:::'## ##:::. ##:: ###:: ##: ###:: ##: ##.....::... ##..::
 ####'####::'##:. ##::: ##:: ####: ##: ####: ##: ##:::::::::: ##::::
 ## ### ##:'##:::. ##:: ##:: ## ## ##: ## ## ##: ######:::::: ##::::
 ##. #: ##: #########:: ##:: ##. ####: ##. ####: ##...::::::: ##::::
 ##:.:: ##: ##.... ##:: ##:: ##:. ###: ##:. ###: ##:::::::::: ##::::
 ##:::: ##: ##:::: ##:'####: ##::. ##: ##::. ##: ########:::: ##::::
..:::::..::..:::::..::....::..::::..::..::::..::........:::::..:::::
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 0;  // not used anymore
        consensus.BIP16Exception = uint256S("0x0000000021f2bed6c2142ab2f5dbb3e5ce41f142875962edc8735cc2943214f2");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0000000021f2bed6c2142ab2f5dbb3e5ce41f142875962edc8735cc2943214f2");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0; 
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 5 * 60;
        consensus.nPowTargetSpacing = 5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1800;
        consensus.nMinerConfirmationWindow = 2400;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000001b22cb417ee4775646b");
        consensus.defaultAssumeValid = uint256S("0x0000000000000001246b0ae9639abb7b59dcfff8dd8ee57df37360c816f76e85");

        pchMessageStart[0] = 0xb7;
        pchMessageStart[1] = 0xa8;
        pchMessageStart[2] = 0xd9;
        pchMessageStart[3] = 0xc6;
        nDefaultPort = 11388;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        genesis = CreateGenesisBlockMainNet(1682231417, 1132948408, 0x1d00ffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000000021f2bed6c2142ab2f5dbb3e5ce41f142875962edc8735cc2943214f2"));
        assert(genesis.hashMerkleRoot == uint256S("0x71bfacebcf45cfe340a323b2f03ee006da5687f4e09688d1bba77f386e60e69e"));

        vSeeds.emplace_back("144.91.107.170");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,61);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,188);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB1, 0x3F};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xF2};

        bech32_hrp = "reversedbitcoin";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;

        checkpointData = {
            {
                { 0, uint256S("0x0000000021f2bed6c2142ab2f5dbb3e5ce41f142875962edc8735cc2943214f2")},
                { 1, uint256S("0x005e25fdcec602ddc789cf25a6246437b5c5f6530d50a3be1e20a2d150ad4e20")},
                { 16, uint256S("0x00001db679d3b81d9c5702341fcc3702a8d431e6545a8e6e149ccf114f19ba17")},
                { 101, uint256S("0x0000001020542fac36dcf70565d41e0f6b833f7cf30809673d6045f6d858533c")},
                { 105, uint256S("0x0000001a48431db9764f9e2194362ef2545397482c2cb05cd117cb1a0702e37e")},
                { 1568, uint256S("0x00000000002f2f360eed0ad8e3837d533e949c36b6f901085b71f822269d88da")},
                { 1755, uint256S("0x00000000000000bf6180d773024183b8557b2f243b6365fe9ffd1aa665725fdd")},
                { 9583, uint256S("0x0000000000000010c53cb2993b759a9a3afc9697b1c77b7b300fb7a957d79e6f")},
                { 12480, uint256S("0x0000000000000001246b0ae9639abb7b59dcfff8dd8ee57df37360c816f76e85")},
            }
        };

        chainTxData = ChainTxData{ 1691898439, 26420, 0.00628957};
    }
};


/**
'########:'########::'######::'########:'##::: ##:'########:'########:
... ##..:: ##.....::'##... ##:... ##..:: ###:: ##: ##.....::... ##..::
::: ##:::: ##::::::: ##:::..::::: ##:::: ####: ##: ##:::::::::: ##::::
::: ##:::: ######:::. ######::::: ##:::: ## ## ##: ######:::::: ##::::
::: ##:::: ##...:::::..... ##:::: ##:::: ##. ####: ##...::::::: ##::::
::: ##:::: ##:::::::'##::: ##:::: ##:::: ##:. ###: ##:::::::::: ##::::
::: ##:::: ########:. ######::::: ##:::: ##::. ##: ########:::: ##::::
:::..:::::........:::......::::::..:::::..::::..::........:::::..:::::
 */

class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 0;
        consensus.BIP16Exception = uint256S("0x000000002544bdd1cbf387abc92847f6ee463cb42a9aac5ea7f3e7a69cb6c6d0");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x000000002544bdd1cbf387abc92847f6ee463cb42a9aac5ea7f3e7a69cb6c6d0");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 5 * 60;
        consensus.nPowTargetSpacing = 5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 180;
        consensus.nMinerConfirmationWindow = 240;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");
        consensus.defaultAssumeValid = uint256S("0x000000002544bdd1cbf387abc92847f6ee463cb42a9aac5ea7f3e7a69cb6c6d0");

        pchMessageStart[0] = 0xa0;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xa6;
        pchMessageStart[3] = 0xa1;
        nDefaultPort = 21388;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        genesis = CreateGenesisBlockTestNet(1682231487, 1077655449, 0x1d00ffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000000002544bdd1cbf387abc92847f6ee463cb42a9aac5ea7f3e7a69cb6c6d0"));
        assert(genesis.hashMerkleRoot == uint256S("0xe61e42a017a088be6864e9b60a52649fefe7682eb6731e47d07647689358d24d"));

        vFixedSeeds.clear();
        vSeeds.clear();

      //  vSeeds.emplace_back("");


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,141);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x07, 0x45, 0x87, 0xCE};
        base58Prefixes[EXT_SECRET_KEY] = {0x07, 0x45, 0x84, 0x91};

        bech32_hrp = "treversedbitcoin";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;


        checkpointData = {
            {
                {0, uint256S("0x000000002544bdd1cbf387abc92847f6ee463cb42a9aac5ea7f3e7a69cb6c6d0")},
            }
        };

        chainTxData = ChainTxData{ 1682231487, 0, 0.00000};
    }
};


/**
'########::'########::'######:::'########:'########::'######::'########:
 ##.... ##: ##.....::'##... ##::... ##..:: ##.....::'##... ##:... ##..::
 ##:::: ##: ##::::::: ##:::..:::::: ##:::: ##::::::: ##:::..::::: ##::::
 ########:: ######::: ##::'####:::: ##:::: ######:::. ######::::: ##::::
 ##.. ##::: ##...:::: ##::: ##::::: ##:::: ##...:::::..... ##:::: ##::::
 ##::. ##:: ##::::::: ##::: ##::::: ##:::: ##:::::::'##::: ##:::: ##::::
 ##:::. ##: ########:. ######:::::: ##:::: ########:. ######::::: ##::::
..:::::..::........:::......:::::::..:::::........:::......::::::..:::::
 */

class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 0;
        consensus.BIP16Exception = uint256S("0x427d54e224d12de5cd412aa9bc7055e2a17f6aec01c0f25b35923a14c0446393");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x427d54e224d12de5cd412aa9bc7055e2a17f6aec01c0f25b35923a14c0446393");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 1 * 60;
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;
        consensus.nMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000200020");
        consensus.defaultAssumeValid = uint256S("0x427d54e224d12de5cd412aa9bc7055e2a17f6aec01c0f25b35923a14c0446393");

        pchMessageStart[0] = 0xb0;
        pchMessageStart[1] = 0xb0;
        pchMessageStart[2] = 0xb0;
        pchMessageStart[3] = 0xb0;
        nDefaultPort = 31388;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        genesis = CreateGenesisBlockRegTest(1682231524, 3, 0x207fffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x427d54e224d12de5cd412aa9bc7055e2a17f6aec01c0f25b35923a14c0446393"));
        assert(genesis.hashMerkleRoot == uint256S("0x21fd76dc62cd5bb2d3c6f2f04fef5002059231ad449c8e664f4a66ccda6396f9"));

        vFixedSeeds.clear();
        vSeeds.clear();

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;

        checkpointData = {
            {
                {0, uint256S("0x427d54e224d12de5cd412aa9bc7055e2a17f6aec01c0f25b35923a14c0446393")},
            }
        };

        chainTxData = ChainTxData{ 1682231524, 0, 0.00000};

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,123);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,179);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x80, 0xCB};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x84, 0x94};

        bech32_hrp = "rreversedbitcoin";
    }

    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (gArgs.IsArgSet("-segwitheight")) {
        int64_t height = gArgs.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
