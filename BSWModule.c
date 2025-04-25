// Example within a DEM event reporting function
Std_ReturnType Dem_ReportErrorStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus) {
  // ... other DEM logic ...
  if (EventId == DEM_EVENT_LB_OFF) {
    if (EventStatus == DEM_EVENT_STATUS_FAILED) {
      // Log the LB_OFF failure
      Dem_SetEventMemoryEntry(EventId, DEM_EVENT_STATUS_FAILED);
      // Potentially trigger a specific diagnostic routine or indicator
      // ...
    } else if (EventStatus == DEM_EVENT_STATUS_PASSED) {
      // Log the LB_OFF recovery
      Dem_SetEventMemoryEntry(EventId, DEM_EVENT_STATUS_PASSED);
      // Potentially clear a related diagnostic routine or indicator
      // ...
    }
  }
  // ... more DEM logic ...
  return E_OK;
}
