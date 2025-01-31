#include "Editor.h"
#include "ECS.h"
#include "Renderer.h"
#include <Array.h>
#include <Error.h>
#include <assert.h>
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>

static ImGuiID AdapterIdxToStorageId_Array(ImGuiSelectionBasicStorage *self,
                                           int idx) {
  return ((Entity *)self->UserData)[idx];
}

void RenderEditor() {
  SDL_Rect windowRect;
  SDL_GetRenderViewport(GetRenderer(), &windowRect);

  // Entity shower
  igSetNextWindowPos((ImVec2){0, 0}, ImGuiCond_None, (ImVec2){0, 0});
  igSetNextWindowSize((ImVec2){windowRect.w / 5.0, windowRect.h},
                      ImGuiCond_Once);
  igSetNextWindowSizeConstraints((const ImVec2){20, windowRect.h},
                                 (const ImVec2){windowRect.w, windowRect.h},
                                 NULL, NULL);
  igBegin("EntityShower", NULL,
          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
              ImGuiWindowFlags_NoTitleBar);

  Entity *entities = GetAllEntitieIDs();
  static ImGuiSelectionBasicStorage selection;
  selection.UserData = entities;
  selection.AdapterIndexToStorageId = AdapterIdxToStorageId_Array;

  ImGuiMultiSelectIO *ms_io = igBeginMultiSelect(
      ImGuiMultiSelectFlags_None, selection.Size, GetArrayLen(entities));

  ImGuiSelectionBasicStorage_ApplyRequests(&selection, ms_io);

  for (int idx = 0; idx < GetArrayLen(entities); idx++) {
    bool item_is_selected =
        ImGuiSelectionBasicStorage_Contains(&selection, entities[idx]);
    igSetNextItemSelectionUserData(idx);
    char name[32] = "Entity :3 : ";
    snprintf(name + 12, 32 - 12, "%lx", entities[idx]);
    igSelectable_Bool(name, item_is_selected,
                      ImGuiSelectableFlags_SpanAvailWidth, (ImVec2){200, 15});
  }
  ms_io = igEndMultiSelect();
  ImGuiSelectionBasicStorage_ApplyRequests(&selection, ms_io);

  igEnd();
  igShowDemoWindow(NULL);
}
