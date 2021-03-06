local f=assert(io.open("D:\\Documents\\GitHub\\localHub\\ide\\ldtWorkplace\\xml_paser\\src\\content.xml",'r'))
local t=f:read("*all")
print(t)
print("================================")
local SLAXML = require 'slaxml'

local myxml=io.open("D:\\Documents\\GitHub\\localHub\\ide\\ldtWorkplace\\xml_paser\\src\\content.xml"):read("*all")
-- Specify as many/few of these as you like
parser = SLAXML:parser{
  startElement = function(name,nsURI,nsPrefix)       end, -- When "<foo" or <x:foo is seen
  attribute    = function(name,value,nsURI,nsPrefix) 
    print ("name is "..name,"value is "..value) 
  end, -- attribute found on current element
  closeElement = function(name,nsURI)                end, -- When "</foo>" or </x:foo> or "/>" is seen
  text         = function(text)     
    print("the text is "..text)                 
  end, -- text and CDATA nodes
  comment      = function(content)                   end, -- comments
  pi           = function(target,content)            end, -- processing instructions e.g. "<?yes mon?>"
}

-- Ignore whitespace-only text nodes and strip leading/trailing whitespace from text
-- (does not strip leading/trailing whitespace from CDATA)

parser:parse(myxml,{stripWhitespace=true})

print("========test if catch the xml=================")
local a= require("slaxml")
a:parse(myxml)