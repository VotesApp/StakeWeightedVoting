/*
 * Copyright 2015 Follow My Vote, Inc.
 * This file is part of The Follow My Vote Stake-Weighted Voting Application ("SWV").
 *
 * SWV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SWV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SWV.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef STUBCHAINADAPTOR_H
#define STUBCHAINADAPTOR_H

#include <QObject>
#include <QMap>

#include <capnp/message.h>

#include <kj/async.h>

#include <vector>

#include "StubChainAdaptor_global.hpp"
#include "BlockchainAdaptorInterface.hpp"

namespace swv {

class STUBCHAINADAPTORSHARED_EXPORT StubChainAdaptor : public QObject, public BlockchainAdaptorInterface
{
    Q_OBJECT

public:
    StubChainAdaptor(QObject* parent = nullptr);
    virtual ~StubChainAdaptor() noexcept;

    virtual kj::Promise<Coin::Reader> getCoin(quint64 id) const;
    virtual kj::Promise<Coin::Reader> getCoin(QString symbol) const;
    virtual kj::Promise<kj::Array<Coin::Reader>> listAllCoins() const;
    virtual kj::Promise<kj::Array<QString>> getMyAccounts() const;
    virtual kj::Promise<Balance::Reader> getBalance(QByteArray id) const;
    virtual kj::Promise<kj::Array<Balance::Reader>> getBalancesForOwner(QString owner) const;
    virtual kj::Promise<::Contest::Reader> getContest(QByteArray contestId) const;

    virtual ::Datagram::Builder createDatagram();
    virtual kj::Promise<void> publishDatagram(QByteArray payerBalanceId, QByteArray publisherBalanceId);
    virtual kj::Promise<::Datagram::Reader> getDatagram(QByteArray balanceId, QString schema) const;

protected:
    capnp::MallocMessageBuilder message;
    std::vector<capnp::Orphan<Coin>> coins;
    std::vector<capnp::Orphan<Contest>> contests;
    std::map<QString, std::vector<capnp::Orphan<Balance>>> balances;
    std::map<QByteArray, capnp::Orphan<::Datagram>> datagrams;
    kj::Maybe<capnp::Orphan<::Datagram>> pendingDatagram;

    kj::Maybe<capnp::Orphan<Balance>&> getBalanceOrphan(QByteArray id);
    kj::Maybe<const capnp::Orphan<Balance>&> getBalanceOrphan(QByteArray id) const;
};

} // namespace swv

#endif // STUBCHAINADAPTOR_H
