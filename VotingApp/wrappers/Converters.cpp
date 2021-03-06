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

#include "Converters.hpp"

QByteArray convertBlob(capnp::Data::Reader data) {
    return QByteArray(reinterpret_cast<const char*>(data.begin()), static_cast<signed>(data.size()));
}

QVariantMap convertListedContest(ContestGenerator::ListedContest::Reader contest) {
    return {{"contestId", QString(convertBlob(contest.getContestId()).toHex())},
            {"votingStake", qint64(contest.getVotingStake())},
            {"tracksLiveResults", contest.getTracksLiveResults()}};
}
