from Move import Move

class Agent:
    def __init__(self):
        self.moves = []
        self.pastcards = []
        self.pastmoves = []

    def reset(self):
        del self.moves[:]
        del self.pastcards[:]
        del self.pastmoves[:]

    def select(self):
        if len(self.moves) > 0:
            if self.moves[0].priority >= 0:
                self.pastcards.append(self.moves[0].card)
                self.pastmoves.append(self.moves[0])
                return self.moves[0]
        else:
            return None

    def updatemoves(self, talon, builds, suits):
        del self.moves[:]
        for build1 in builds:
            if len(build1.cards) > 0:
                if build1.cards[-1].value == 1:
                    for suit in suits:
                        if len(suit.cards) == 0:
                            move = Move(1, build1.cards[-1], build1, suit)
                            if self.checkmove(move):
                                self.moves.append(move)
                for suit in suits:
                    if (len(suit.cards) > 0 and
                    build1.cards[-1].suit == suit.cards[-1].suit and
                    build1.cards[-1].value - 1 == suit.cards[-1].value):
                        move = Move(1, build1.cards[-1], build1, suit)
                        if self.checkmove(move):
                            self.moves.append(move)
                otherbuilds = list(builds)
                otherbuilds.remove(build1)
                cards = list(self.visiblecards(build1))

                for build2 in otherbuilds:
                    for card in cards:
                        if card.value == 13 and len(build2.cards) == 0:
                            priority = len(build1.cards)
                            move = Move(priority, card, build1, build2)
                            if self.checkmove(move):
                                self.moves.append(move)
                        if len(build2.cards) > 0:
                            if (card.value == build2.cards[-1].value - 1 and
                            card.color != build2.cards[-1].color):
                                priority = len(build1.cards)
                                move = Move(priority, card, build1, build2)
                                if self.checkmove(move):
                                    self.moves.append(move)

        if talon.cards:
            taloncard = talon.cards[-1]
            if taloncard.value == 1:
                for suit in suits:
                    if len(suit.cards) == 0:
                        move = Move(1, taloncard, talon, suit)
                        if self.checkmove(move):
                            self.moves.append(move)
                            break
            if taloncard.value == 13:
                for build in builds:
                    if len(build.cards) == 0:
                        move = Move(1, taloncard, talon, build)
                        if self.checkmove(move):
                            self.moves.append(move)
                            break

            for suit in suits:
                if (len(suit.cards) > 0 and
                taloncard.suit == suit.cards[-1].suit and
                taloncard.value - 1 == suit.cards[-1].value):
                    move = Move(1, taloncard, talon, suit)
                    if self.checkmove(move):
                        self.moves.append(move)
                        break
                    
            for build in builds:
                if len(build.cards) > 0:
                    if not build.cards[-1].face_shown:
                        build.showtop
                    if (taloncard.value == build.cards[-1].value - 1
                    and taloncard.color != build.cards[-1].color
                    and len(build.cards) > 0):
                        move = Move(1, taloncard, talon, build)
                        if self.checkmove(move):
                            self.moves.append(move)

        if len(self.moves) > 0:
            self.moves = sorted(self.moves, key=lambda x: x.priority, reverse=True)

    def checkmove(self, move):
        if move.source.type == "Talon" or move.dest.type == "Suit":
            return True
        if len(move.source.cards) > 1 and len(move.dest.cards) > 1:
            visible = self.visiblecards(move.source)
            remnants = [x for x in move.source.cards if x not in visible]
            if (remnants
            and remnants[-1].face_shown
            and remnants[-1].color == move.dest.cards[-1].color):
                return False
        if move.card.value == 13 and move.card == move.source.cards[0]:
            return False
        if (move.card in self.pastcards) and move.card == move.source.cards[-1]:
            return False
        for pastmove in self.pastmoves:
            if (move.card == pastmove.card
            and move.source == pastmove.source
            and move.dest == pastmove.dest
            and move.sourcelen == pastmove.sourcelen
            and move.destlen == pastmove.destlen):
                return False
        return True

    def visiblecards(self, stack):
        visible = []
        for card in stack.cards:
            if card.face_shown:
                visible.append(card)
        return visible

    def play(self, talon, builds, suits):
        self.updatemoves(talon, builds, suits)
        return self.select()
