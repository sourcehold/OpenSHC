local exports = {}

exports.enable = function(self, moduleConfig, globalConfig)
  local requireTable = require("OpenSHC.dll") -- loads the dll in memory and runs luaopen_OpenSHC
end

exports.disable = function(self, moduleConfig, globalConfig) error("not implemented") end

return exports
