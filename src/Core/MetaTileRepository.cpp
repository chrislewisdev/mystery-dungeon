#include "Core/MetaTileRepository.h"

void MetaTileRepository::store(MetaTile metaTile) {
    metaTiles[metaTile.getId()] = metaTile;
}

MetaTile& MetaTileRepository::get(MetaTileId id) {
    return metaTiles.at(id);
}
