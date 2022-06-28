# CommBus
Communication bus network. Using the nanomsg pub-sub protocol https://nanomsg.org/. For communication with distributed dictionary networks

- Note this library is a C++17 implementation

[![Build Status](https://dev.azure.com/ConnorBuchel0890/A-Loose-Screw/_apis/build/status/A-Loose-Screw.CommBus?branchName=master)](https://dev.azure.com/ConnorBuchel0890/A-Loose-Screw/_build/latest?definitionId=23&branchName=master)

## Implementation Of ordered dictionary
- General idea

### Ordered Step process
1. Singular Server running which will store all named tables (each client will also have it's own storage for the table)
2. Create/Subscribe to a table e.g `Drivetrain`
3. Table will have entries e.g `Drivetrain/gearbox` / `table()->getEntry('gearbox');`
4. You can either set, or get this entry. `Drivetrain/gearbox/set/value` / `table()->getEntry('gearbox').setFloat(3.5)`
5. Other clients can call a scan to the server. Of which the server will respond with the names of each table and entry. The client can then use this set/get those values. (good for a UI)
