#include "vehicle_selector.h"

#include "game.h"
#include "vpart_position.h"
#include "map.h"

vehicle_selector::vehicle_selector( const tripoint &pos, int radius, bool accessible,
                                    bool for_crane_lift )
{
    for( const auto &e : closest_tripoints_first( radius, pos ) ) {
        if( !accessible ||
            ( for_crane_lift ? g->m.sees( pos, e, radius ) : g->m.clear_path( pos, e, radius, 1, 100 ) ) ) {
            if( const optional_vpart_position vp = g->m.veh_at( e ) ) {
                data.emplace_back( vp->vehicle(), vp->part_index() );
            }
        }
    }
}

vehicle_selector::vehicle_selector( const tripoint &pos, int radius, bool accessible,
                                    const vehicle &ignore )
{
    for( const auto &e : closest_tripoints_first( radius, pos ) ) {
        if( !accessible || g->m.clear_path( pos, e, radius, 1, 100 ) ) {
            if( const optional_vpart_position vp = g->m.veh_at( e ) ) {
                if( &vp->vehicle() != &ignore ) {
                    data.emplace_back( vp->vehicle(), vp->part_index() );
                }
            }
        }
    }
}
