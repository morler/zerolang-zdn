#ifndef ZERO_C_ZDN_FORMAT_H
#define ZERO_C_ZDN_FORMAT_H

#include "zero.h"

// ── ZDN (Zero Data Notation) CLI Output Format ──
//
// ZDN is an agent-first structured output format that reuses Zero's row syntax.
// It serves as an alternative to --json for machine-readable compiler output.
//
// Syntax rules:
//   - Top-level record name (e.g. "CheckResult") on its own line
//   - Fields: `fieldName value`, one per line, 2-space indented
//   - Strings: `"quoted"` (same escaping as JSON)
//   - Nested objects: indented by 2 more spaces
//   - Arrays: indented items, one per line; empty = `[]`
//   - Null: `null`

// ── Low-level ZDN building blocks ──

// Append a quoted and escaped string value (identical to JSON string rules)
void zdn_append_string(ZBuf *buf, const char *value);

// Append a null literal
void zdn_append_null(ZBuf *buf);

// Append a simple field: `fieldName value\n`
void zdn_field_string(ZBuf *buf, const char *name, const char *value, int indent);
void zdn_field_int(ZBuf *buf, const char *name, long long value, int indent);
void zdn_field_bool(ZBuf *buf, const char *name, bool value, int indent);
void zdn_field_nullable_string(ZBuf *buf, const char *name, const char *value, int indent);
void zdn_field_nullable_int(ZBuf *buf, const char *name, long long value, int indent);

// Start/end a nested object: `fieldName\n` then indented content, then dedent
void zdn_object_start(ZBuf *buf, const char *name, int indent);
void zdn_object_end(ZBuf *buf, int indent); // writes nothing; just a marker

// Start/end an array: `fieldName\n` then items, dedent
// Empty arrays use `fieldName []\n`
void zdn_array_start(ZBuf *buf, const char *name, int indent);
void zdn_array_end(ZBuf *buf, int indent);
void zdn_array_item_string(ZBuf *buf, const char *value, int indent);
void zdn_array_item_int(ZBuf *buf, long long value, int indent);

// ── Command-specific ZDN output ──

// Print diagnostics (error case) in ZDN format -> stdout
void zdn_print_diag(const char *path, const ZDiag *diag);

// Print check success in ZDN format -> stdout
void zdn_print_check_success(const char *path, const SourceInput *input,
                             const Program *program, const ZTargetInfo *target);

// Print build result in ZDN format -> stdout
void zdn_print_build(const char *source_file, const char *emit_kind,
                     const char *target_name, const char *profile,
                     const char *artifact_path, long long artifact_bytes,
                     long long elapsed_ms);

#endif // ZERO_C_ZDN_FORMAT_H
