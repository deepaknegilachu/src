local settings = require "settings"
local select = require "select"

local engines = settings.window.search_engines

engines.ddg = "https://www.duckduckgo.com/?q=%s"
engines.brave = "https://search.brave.com/search?q=%s"
engines.searx = "https://searx.prvcy.eu/search?q=%s"
engines.default = engines.ddg

settings.window.home_page = "https://www.duckduckgo.com"

select.label_maker = function ()
    local chars = charset("asdfjkl;")
    return trim(sort(reverse(chars)))
end
