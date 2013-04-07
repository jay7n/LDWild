--[[
   
local print = print

level1 = {}
setfenv(1, level1)

filetype = "png"
filename = "props1.plist"
mapname = "scene.tmx"

local propscontent = {
      "wall",
      "s_frame",
      "s_chair",
      "s_deckchair"
   }

print"hello, I'm lua!"
   
--]]


level = {
   filetype = "png",
   plistname = "props1.plist",
   mapname = "scene.tmx",

   propscontent = {
      "frame",
      "chair",
      "deckchair"
   },
   
   getprop = function(idx, with_file_suffix)
      local prop = level.propscontent[idx]
      return  with_file_suffix and prop.."."..level.filetype or prop
   end
}
   