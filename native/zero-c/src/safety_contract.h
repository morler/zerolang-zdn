#ifndef ZERO_SAFETY_CONTRACT_H
#define ZERO_SAFETY_CONTRACT_H

#include "zero.h"

#include <stdbool.h>

typedef struct {
  const char *canonical_profile;
  const char *profile_key;
  const char *bounds_policy;
  const char *overflow_policy;
  bool optimizer_elision;
} ZSafetyFactsProfile;

void z_append_safety_facts_json(ZBuf *buf, const ZSafetyFactsProfile *profile);

#endif
