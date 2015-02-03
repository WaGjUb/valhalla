#include <string.h>
#include "baldr/graphtileheader.h"
#include "baldr/nodeinfo.h"
#include "baldr/directededge.h"
#include "baldr/edgeinfo.h"
#include "config.h"

namespace valhalla {
namespace baldr {

// Default constructor. This is written with GraphTileHeaderBuilder and
// read within GraphTile. Set the version and internal version here so a
// "default" GraphTileHeader can be used to compare to what is read from
// a tile.
GraphTileHeader::GraphTileHeader()
    : date_created_{},
      nodecount_(0),
      directededgecount_(0),
      edgeinfo_offset_(0),
      textlist_offset_(0),
      exitlist_offset_(0),
      admin_offset_(0),
      merlist_offset_(0) {
  internal_version_ = NodeInfo::internal_version() +
                      DirectedEdge::internal_version() +
                      GraphId::internal_version();
  strncpy(version_, PACKAGE_VERSION, kMaxVersionSize);
  version_[kMaxVersionSize-1] = 0;
}

// Get the internal version
int64_t GraphTileHeader::internal_version() const {
  return internal_version_;
}

// Get the date created
uint64_t GraphTileHeader::date_created() const {
  return date_created_;
}

// Get the version string.
std::string GraphTileHeader::version() const {
  return version_;
}

// Get the count of nodes in the tile.
uint32_t GraphTileHeader::nodecount() const {
  return nodecount_;
}

// Get the count of directed edges in the tile.
uint32_t GraphTileHeader::directededgecount() const {
  return directededgecount_;
}

// Get the offset in bytes to the start of the edge information.
uint32_t GraphTileHeader::edgeinfo_offset() const {
  return edgeinfo_offset_;
}

// Get the offset in bytes to the start of the text / names list.
uint32_t GraphTileHeader::textlist_offset() const {
  return textlist_offset_;
}

// Gets the offset in bytes to the exit list.
uint32_t GraphTileHeader::exitlist_offset() const {
  return exitlist_offset_;
}

// Get the offset in bytes to the administrative information. (TODO)
uint32_t GraphTileHeader::admin_offset() const {
  return admin_offset_;
}

// Get the offset in bytes to the Multi-Edge Restriction list. (TODO)
uint32_t GraphTileHeader::merlist_offset() const {
  return merlist_offset_;
}

}
}
