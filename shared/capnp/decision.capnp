# Copyright 2015 Follow My Vote, Inc.
# This file is part of The Follow My Vote Stake-Weighted Voting Application ("SWV").
#
# SWV is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SWV is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SWV.  If not, see <http://www.gnu.org/licenses/>.

@0x9d1e6685c0b5a466;

using Contestant = import "contest.capnp".UnsignedContest.Contestant;

struct Decision {
# A Decision is a vote on a particular contest. A decision specifies the voter's opinions on one or more contestants,
# and for some contest types, may define a list of additional write-in contestants who were not specified in the
# original contest.
#
# An opinion is represented as an integer value assigned to a specific contestant. The semantics of this number depend
# on the specific contest being evaluated. The tags on the associated contest should suffice to disambiguate which
# counting algorithm is used to parse the opinions.

    id @0 :Data;
    # ID of this decision
    contest @1 :Data;
    # ID of the contest this decision pertains to
    opinions @2 :List(Opinion);
    # List of opinions within this decision
    writeIns @3 :List(Contestant);
    # List of write-in candidates specified in this decision

    struct Opinion {
        contestant @0 :Int32;
        # Index into contest->contestants, overflow into writeIns
        opinion @1 :Int32;
        # The integral opinion on the specified contestant
    }
}
