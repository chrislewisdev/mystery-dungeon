#pragma once

typedef MetaTileId u16;

struct MetaTileAttributes {
    bool isSolid;
};

class MetaTile {
    private:
        MetaTileId id;
        MetaTileAttributes attributes;
    public:
        MetaTile(MetaTileId id): id(id) {}
        const MetaTileAttributes& getAttributes() { return attributes; }
};