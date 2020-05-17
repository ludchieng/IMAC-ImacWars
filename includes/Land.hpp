/*
 * Land.hpp
 */

#ifndef LAND_HPP
#define LAND_HPP

class Land {
public:
    enum Type {
        PLAIN = (1<<0),
        OCEAN = (1<<1),
        COAST = (1<<2),
        SHORE = (1<<3),
        FOREST = (1<<4),
        MOUNTAIN = (1<<5),
        PEAK = (1<<6)
    };
    
    static const Land::Type TYPE_FIELD = (Land::Type) (Land::Type::PLAIN | Land::Type::SHORE | Land::Type::FOREST);
    static const Land::Type TYPE_ALL = (Land::Type) (Land::Type::PLAIN | Land::Type::OCEAN | Land::Type::COAST | Land::Type::SHORE | Land::Type::FOREST | Land::Type::MOUNTAIN | Land::Type::PEAK);
};

#endif /* LAND_HPP */
