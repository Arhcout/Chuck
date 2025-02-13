#include "Editor.h"
#include "ECS.h"
#include "Renderer.h"
#include <Array.h>
#include <Error.h>
#include <assert.h>
#include <map.h>
#include <stdlib.h>

// clang-format off
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
// clang-format on

#define DEFAULT_STEP_SIZEF 0.1
#define DEFAULT_FAST_STEP_SIZEF 1
#define DEFAULT_STEP_SIZEI 1
#define DEFAULT_FAST_STEP_SIZEI 5

static uint64_t widgetID = 0;
static hashmap *selection;

static hashmap *entityNames;

void SetEntityNames(hashmap *names) {
  assert(names);
  entityNames = names;
}

static void RenderWidgetTransformComponent(Entity *e) {
  Transform *cmp = GetComponent(e, Transform);
  if (!cmp)
    return;

  igSeparator();
  igText("Transform");
  igInputFloat2("Position", (float *)&cmp->pos, "%.2f",
                ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
  igInputFloat2("Scale", (float *)&cmp->scale, "%.2f",
                ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
  igInputFloat("Rotation", (float *)&cmp->rotation, DEFAULT_STEP_SIZEF, DEFAULT_FAST_STEP_SIZEF,
               "%.2f", ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
  igInputInt("Layer", &cmp->layer, DEFAULT_STEP_SIZEI, DEFAULT_FAST_STEP_SIZEI,
             ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
}

static void RenderWidgetSpriteComponent(Entity *e) {
  Sprite *cmp = GetComponent(e, Sprite);
  if (!cmp)
    return;

  igSeparator();
  igTextColored(cmp->enabled ? (ImVec4){1, 1, 1, 1} : (ImVec4){0.5, 0.5, 0.5, 1}, "Sprite");
  igPushID_Str("spr_enable");
  igCheckbox("Enabled", &cmp->enabled);
  igPopID();
  igInputFloat2("Offset", (float *)&cmp->offset, "%.2f",
                ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
  igInputFloat2("Image Scale", (float *)&cmp->scale, "%.2f",
                ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
  igInputFloat("Image Rotation", (float *)&cmp->rotation, DEFAULT_STEP_SIZEF,
               DEFAULT_FAST_STEP_SIZEF, "%.2f",
               ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
}
static void RenderWidgetScriptComponent(Entity *e) {
  Script *cmp = GetComponent(e, Script);
  if (!cmp)
    return;
  igSeparator();
  igTextColored(cmp->enabled ? (ImVec4){1, 1, 1, 1} : (ImVec4){0.5, 0.5, 0.5, 1}, "Script");
  igPushID_Str("scr_enable");
  igCheckbox("Enabled", &cmp->enabled);
  igPopID();
}

static int GetFirstSelectedEntity(const void *key, size_t ksize, uintptr_t value, void *usr) {
  if ((bool)value == false) {
    return 0; // continue
  }
  *(size_t *)usr = *(size_t *)key;
  return -1; // Abort
}

static int FreeKey(const void *key, size_t ksize, uintptr_t value, void *usr) {
  assert(key);
  free((void *)key);
  return 0;
}

void InitEditor() { selection = hashmap_create(); }

void UninitEditor() { DestroyArray(selection); }

void RenderEditor() {
  assert(selection && "RenderEditor: selection is NULL you need to call InitEditor");
  widgetID = 0;
  SDL_Rect windowRect;
  SDL_GetRenderViewport(GetRenderer(), &windowRect);

  // Entity shower
  igSetNextWindowPos((ImVec2){0, 0}, ImGuiCond_None, (ImVec2){0, 0});
  igSetNextWindowSize((ImVec2){windowRect.w / 5.0, windowRect.h}, ImGuiCond_Once);
  igSetNextWindowSizeConstraints((const ImVec2){20, windowRect.h},
                                 (const ImVec2){windowRect.w, windowRect.h}, NULL, NULL);
  igBegin("EntityShower", NULL,
          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

  Entity *entities = GetAllEntitieIDs();

  // NOTE: might add cliper if lot's of entities in scene (1k+)
  ImGuiMultiSelectIO *ms_io =
      igBeginMultiSelect(ImGuiMultiSelectFlags_None, GetArrayLen(entities), GetArrayLen(entities));

  for (size_t i = 0; i < GetArrayLen(entities); i++) {
    igPushID_Int(widgetID);
    widgetID++;
    igSetNextItemSelectionUserData(i);
    bool selected;
    size_t j = i;
    hashmap_get(selection, &j, sizeof(size_t), (uintptr_t *)&selected);
    const char *name;
    hashmap_get(entityNames, &entities[i], sizeof(Entity), (uintptr_t *)&name);
    igSelectable_Bool(name, selected, ImGuiSelectableFlags_SpanAvailWidth, (ImVec2){100, 15});
    igPopID();
  }

  ms_io = igEndMultiSelect();

  for (size_t r = 0; r < ms_io->Requests.Size; r++) {
    ImGuiSelectionRequest req = ms_io->Requests.Data[r];
    int type = req.Type;
    switch (type) {
    case ImGuiSelectionRequestType_SetRange:
      for (size_t i = req.RangeFirstItem; i <= req.RangeLastItem; i++) {
        size_t *key = malloc(sizeof(size_t));
        *key = i;
        hashmap_set_free(selection, key, sizeof(size_t), req.Selected, FreeKey, NULL);
      }
      break;
    case ImGuiSelectionRequestType_SetAll:
      for (size_t i = 0; i < GetArrayLen(entities); i++) {
        size_t *key = malloc(sizeof(size_t));
        *key = i;
        hashmap_set_free(selection, key, sizeof(size_t), req.Selected, FreeKey, NULL);
      }
      break;
    }
  }

  igEnd();

  // Entity Editor
  igSetNextWindowPos((ImVec2){windowRect.w - windowRect.w / 5.0, 0}, ImGuiCond_Once,
                     (ImVec2){0, 0});
  igSetNextWindowSize((ImVec2){windowRect.w / 5.0, windowRect.h}, ImGuiCond_Once);
  igSetNextWindowSizeConstraints((const ImVec2){20, windowRect.h},
                                 (const ImVec2){windowRect.w, windowRect.h}, NULL, NULL);
  igBegin("EntityViewer", NULL,
          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

  size_t selectedIdx = 0;
  hashmap_iterate(selection, GetFirstSelectedEntity, &selectedIdx);
  for (int i = 0; i < NUM_CMP_TYPE; i++) {
    CmpFnOnType(RenderWidget, i, &entities[selectedIdx]);
  }

  if (igButton("Add component", (ImVec2){igGetWindowWidth(), 15})) {
  }

  igEnd();

  igShowDemoWindow(NULL);
}
