class Move:
    def __init__(self, priority, card, source, dest):
        self.priority = priority
        self.card = card
        self.source = source
        self.sourcelen = len(source.cards)
        self.dest = dest
        self.destlen = len(dest.cards)

    def __repr__(self):
        """Return a string for debug print statements."""
        return "Priority: %r, %r \n %r %r => %r %r" % (self.priority, self.card, self.source.type, self.source.id, self.dest.type, self.dest.id)
