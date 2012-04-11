#ifndef _WAYPOINT_H
#define _WAYPOINT_H
extern char* WPactivated;

void activateWaypoint(char* name);
bool isWaypointActivated(char* name);
void showWPMenu();

#endif
