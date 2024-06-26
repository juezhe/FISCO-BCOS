/*
 *  Copyright (C) 2021 FISCO BCOS.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @file SealerConfig.h
 * @author: yujiechen
 * @date: 2021-05-14
 */
#pragma once
#include "bcos-framework/consensus/ConsensusInterface.h"
#include "bcos-framework/protocol/BlockFactory.h"
#include "bcos-framework/txpool/TxPoolInterface.h"
#include "bcos-tool/NodeTimeMaintenance.h"

namespace bcos::sealer
{
class SealerConfig
{
public:
    using Ptr = std::shared_ptr<SealerConfig>;
    SealerConfig(bcos::protocol::BlockFactory::Ptr _blockFactory,
        bcos::txpool::TxPoolInterface::Ptr _txpool,
        bcos::tool::NodeTimeMaintenance::Ptr _nodeTimeMaintenance)
      : m_txpool(std::move(_txpool)),
        m_blockFactory(std::move(_blockFactory)),
        m_nodeTimeMaintenance(std::move(_nodeTimeMaintenance))
    {}
    virtual ~SealerConfig() = default;

    virtual void setConsensusInterface(bcos::consensus::ConsensusInterface::Ptr _consensus)
    {
        m_consensus = std::move(_consensus);
    }
    virtual bcos::txpool::TxPoolInterface::Ptr txpool() { return m_txpool; }

    virtual unsigned minSealTime() const { return m_minSealTime; }
    virtual void setMinSealTime(unsigned _minSealTime) { m_minSealTime = _minSealTime; }
    virtual void setGroupId(const std::string& _groupId) { m_groupId = _groupId; }
    virtual void setChainId(const std::string& _chainId) { m_chainId = _chainId; }
    virtual const std::string& groupId() const { return m_groupId; }
    virtual const std::string& chainId() const { return m_chainId; }
    virtual bcos::crypto::KeyPairInterface::Ptr keyPair() const { return m_keyPair; }
    virtual void setKeyPair(bcos::crypto::KeyPairInterface::Ptr _keyPair)
    {
        m_keyPair = std::move(_keyPair);
    }

    bcos::protocol::BlockFactory::Ptr blockFactory() { return m_blockFactory; }
    bcos::consensus::ConsensusInterface::Ptr consensus() { return m_consensus; }
    bcos::tool::NodeTimeMaintenance::Ptr nodeTimeMaintenance() { return m_nodeTimeMaintenance; }

protected:
    bcos::crypto::KeyPairInterface::Ptr m_keyPair;
    bcos::txpool::TxPoolInterface::Ptr m_txpool;
    bcos::protocol::BlockFactory::Ptr m_blockFactory;
    bcos::consensus::ConsensusInterface::Ptr m_consensus;
    bcos::tool::NodeTimeMaintenance::Ptr m_nodeTimeMaintenance;
    unsigned m_minSealTime = 500;
    std::string m_groupId{};
    std::string m_chainId{};
};
}  // namespace bcos::sealer