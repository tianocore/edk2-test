#!/usr/bin/env python

import os
import sys
import shutil
import fileinput
import datetime
import uuid
import xml.etree.ElementTree
from collections import namedtuple
import re
import argparse

# configuration file paths

path_to_sctpkg = "../"
path_to_efi_categories = "TestCase/UEFI/EFI/"
path_to_xml = "data.xml"

# test configuration variables

ConfigCategory = ""
ConfigFileGuid = ""
ConfigTestName = ""
ConfigTestDescription = ""
ConfigTestGuid = ""
ConfigTestCaseName = ""
ConfigTestCaseGuid = ""
ConfigTestCaseDescription = ""
ConfigAssertionGuid = ""
ConfigProtocolGuid = ""
ConfigCGFWCategory = ""

# checkpoint variables so the script can undo changes in the event of some failure
CheckPointCreatedFileStructure = False
CheckPointCreatedNewCategoryIni = False
CheckPointCreatedNewCommonGenFrameworkSh = False

#function declarations

def isInt(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def isHex(s):
    try:
        int(s, 16)
        return True
    except ValueError:
        return False

def openFile(path, options):
    try:
        file = open(path, options)
        return file
    except IOError:
        return None

def replaceTextPlaceholderInFile(inFilePath):
    now = datetime.datetime.now()

    renamedInFilePath = ("%s.old" % inFilePath)
    os.rename(inFilePath, renamedInFilePath)

    inFile = openFile(inFilePath, "w")
    if inFile == None:
        print "ERROR: Could not open \"%s\"" % inFilePath
        return 1

    renamedInFile = openFile(renamedInFilePath, "r")
    if inFile == None:
        print "ERROR: Could not open \"%s\"" % renamedInFilePath
        return 1

    for line in renamedInFile:
        line = line.replace("$<currentyear>$", ("%d" % now.year))
        line = line.replace("$<fileguid>$", getHyphenGuid(ConfigFileGuid))
        line = line.replace("$<testname>$", ConfigTestName)
        line = line.replace("$<testnameupper>$", ConfigTestName.upper())
        line = line.replace("$<testdescription>$", ConfigTestDescription)
        line = line.replace("$<testcasename>$", ConfigTestCaseName)
        line = line.replace("$<testcasenameupper>$", ConfigTestCaseName.upper())
        line = line.replace("$<testcasedescription>$", ConfigTestCaseDescription)
        line = line.replace("$<testcaseguid>$", getCodeGuid(ConfigTestCaseGuid))
        line = line.replace("$<assertionguid>$", getCodeGuid(ConfigAssertionGuid))
        if ConfigCategory.name == "ProtocolTest":
            line = line.replace("$<testguid>$", getCodeGuid(ConfigProtocolGuid))
        else:
            line = line.replace("$<testguid>$", getCodeGuid(ConfigTestGuid))
        inFile.write(line)

    inFile.close()
    renamedInFile.close()
    os.remove(renamedInFilePath)

    return 0

def getRawGuid():
    guid = uuid.uuid4()
    s = "%s" % guid.hex
    return s

def getCodeGuid(s):
    return "{ 0x%s, 0x%s, 0x%s, {0x%s, 0x%s, 0x%s, 0x%s, 0x%s, 0x%s, 0x%s, 0x%s }}" % (s[0:8],s[8:12],s[12:16],s[16:18],s[18:20],s[20:22],s[22:24],s[24:26],s[26:28],s[28:30],s[30:])

def getHyphenGuid(s):
    return "%s-%s-%s-%s-%s" % (s[0:8], s[8:12], s[12:16], s[16:20], s[20:32])

def faultHandler(s):
    print "Undoing changes made to file structure..."
    if CheckPointCreatedFileStructure:
        shutil.rmtree(os.path.join(path_to_sctpkg, path_to_efi_categories, ConfigCategory.path, ConfigTestName))
    if CheckPointCreatedNewCategoryIni:
        os.remove(os.path.join(path_to_sctpkg, "Config/Data/Category.ini.new"))
    if CheckPointCreatedNewCommonGenFrameworkSh:
        os.remove(os.path.join(path_to_sctpkg, "CommonGenFramework.sh.new"))
    print "Exiting..."
    sys.exit()

def isValidSentence(s):
    if all(x.isalpha() or x.isspace() or isInt(x) or x == "." for x in s):
        return True
    else:
        return False

# entry point

parser = argparse.ArgumentParser(description='Process output from UEFI in FVP.')
parser.add_argument("-g", "--guid", required=False, default=False, action="store_true", help="Generates a GUID.")
args = parser.parse_args()

if args.guid == True:
    guid = getRawGuid()
    print ""
    print "%s" % getCodeGuid(guid)
    print ""
    print "%s" % getHyphenGuid(guid)
    print ""
    sys.exit()

# welcome text
print "*******************************************************************************"
print "*                   SCT Test Case Template Creation Wizard                    *"
print "*******************************************************************************"
print ""


# requesting category
CategoryEntry = namedtuple("CategoryEntry", "name path uuid")
Categories = []
i = 0
tree = xml.etree.ElementTree.parse(path_to_xml)
root = tree.getroot()
for category in root.findall("category"):
    Categories.append(CategoryEntry(category.find("name").text, category.find("path").text, category.find("uuid").text))
    print "(%d) %s" % (i, Categories[i].name)
    i = i + 1
while True:
    print "Which category do you want to use for your test? (integer)"
    UserString = raw_input("> ")
    if isInt(UserString):
        UserValue = int(UserString)
        if UserValue >= i or UserValue < 0:
            print "Invalid entry \"%s\"" % UserString
        else:
            ConfigCategory = Categories[UserValue]
            print ""
            break
    else:
        print "Invalid entry \"%s\"" % UserString


# if protocol test is selected
if ConfigCategory.name == "ProtocolTest":
    print "You have selected ProtocolTest, you must enter the UUID of the protocol under test now as a string of 32 hex digits."
    while True:
        UserString = raw_input("> ")
        if len(UserString) == 32 and isHex(UserString):
            ConfigTestGuid = UserString
            ConfigProtocolGuid = UserString
            break
        else:
            print "Invalid entry \"%s\"" % UserString
    print ""


# requesting test name
print "What do you want to call your test? (string)"
while True:
    ConfigTestName = raw_input("> ")
    if ConfigTestName.isalnum() == True and os.path.isdir(os.path.join(path_to_sctpkg, path_to_efi_categories, ConfigCategory.path, ConfigTestName)) == False:
        break
    else:
        print "Invalid entry \"%s\"" % ConfigTestName
print ""


# requestion test description
print "Please enter a short (~1 sentence) description of your test. (string)"
while True:
    ConfigTestDescription = raw_input("> ")
    if isValidSentence(ConfigTestDescription):
        break
    else:
        print "Invalid entry \"%s\"" % ConfigTestDescription
print ""


# requesting name of first test case
print "What do you want to call the first test case? (string)"
while True:
    ConfigTestCaseName = raw_input("> ")
    if ConfigTestCaseName.isalnum():
        break
    else:
        print "Invalid entry \"%s\"" % ConfigTestCaseName
print ""


# requesting description of the test case
print "Please enter a short (~1 sentence) description of your test case. (string)"
while True:
    ConfigTestCaseDescription = raw_input("> ")
    if isValidSentence(ConfigTestCaseDescription):
        break
    else:
        print "Invalid entry \"%s\"" % ConfigTestCaseDescription
print ""


# asking where to place the new test in CommonGenFramework.sh
cgfwCategories = []
cgfw = openFile(os.path.join(path_to_sctpkg, "CommonGenFramework.sh"), "r")
if cgfw == None:
    print "ERROR: Could not open \"%s\"" % (os.path.join(path_to_sctpkg, "CommonGenFramework.sh"))
    faultHandler()
print "Groups in CommonGenFramework.sh"
i = 0
for line in cgfw:
    line = line.split()
    if len(line) > 4 and line[0] == "if" and line[1] == "[" and line[2] == "$1" and line[3] == "=":
        cgfwCategories.append(line[4].replace("\"", ""))
        print "(%d) %s" % (i, cgfwCategories[i])
        i = i + 1
print "What group would you like to place your new test in?  Leave it blank if you wish to do this yourself. (integer)"
while True:
    UserString = raw_input("> ")
    if isInt(UserString) and int(UserString) >= 0 and int(UserString) < i:
        ConfigCGFWCategory = cgfwCategories[int(UserString)]
        break
    else:
        print "Invalid entry \"%s\"" % UserString
print ""


# making sure options are correct
print "New Test Parameters"
print "  Category:                 %s" % ConfigCategory.name
print "  Test Name:                %s" % ConfigTestName
print "  Test Description:         %s" % ConfigTestDescription
print "  Test Case Name:           %s" % ConfigTestCaseName
print "  Test Case Description:    %s" % ConfigTestCaseDescription
print "  CommonGenFramework Group: %s" % ConfigCGFWCategory

while True:
    print "Do you wish to apply these changes? (y/n)"
    UserString = raw_input("> ")
    if UserString[0] == "y" or UserString[0] == "Y":
        print ""
        break
    elif UserString[0] == "n" or UserString[0] == "N":
        print "Exiting..."
        sys.exit()
    else:
        print "Invalid entry \"%s\"" % UserString


# building test files
print "Building Test Files..."
PathToTestDirectory = os.path.join(path_to_sctpkg, path_to_efi_categories, ConfigCategory.path, ConfigTestName, "BlackBoxTest")
os.makedirs(PathToTestDirectory)
CheckPointCreatedFileStructure = True
shutil.copyfile("template_BBTest.inf", os.path.join(PathToTestDirectory, ("%sBBTest.inf" % ConfigTestName)))
shutil.copyfile("template_Guid.c", os.path.join(PathToTestDirectory, "Guid.c"))
shutil.copyfile("template_Guid.h", os.path.join(PathToTestDirectory, "Guid.h"))
shutil.copyfile("template_BBTestFunction.c", os.path.join(PathToTestDirectory, ("%sBBTestFunction.c" % ConfigTestName)))
shutil.copyfile("template_BBTestFunction.h", os.path.join(PathToTestDirectory, ("%sBBTestFunction.h" % ConfigTestName)))
shutil.copyfile("template_BBTestMain.c", os.path.join(PathToTestDirectory, ("%sBBTestMain.c" % ConfigTestName)))
shutil.copyfile("template_BBTestMain.h", os.path.join(PathToTestDirectory, ("%sBBTestMain.h" % ConfigTestName)))


# generating guids
print "Generating GUIDs..."
ConfigFileGuid = getRawGuid()
ConfigTestCaseGuid = getRawGuid()
ConfigAssertionGuid = getRawGuid()
if ConfigCategory.name != "ProtocolTest":
    ConfigTestGuid = getRawGuid()


# replacing placeholder text in files
print "Applying changes to templates..."
replaceTextPlaceholderInFile(os.path.join(PathToTestDirectory, ("%sBBTest.inf" % ConfigTestName)))
replaceTextPlaceholderInFile(os.path.join(PathToTestDirectory, "Guid.c"))
replaceTextPlaceholderInFile(os.path.join(PathToTestDirectory, "Guid.h"))
replaceTextPlaceholderInFile(os.path.join(PathToTestDirectory, ("%sBBTestFunction.c" % ConfigTestName)))
replaceTextPlaceholderInFile(os.path.join(PathToTestDirectory, ("%sBBTestFunction.h" % ConfigTestName)))
replaceTextPlaceholderInFile(os.path.join(PathToTestDirectory, ("%sBBTestMain.c" % ConfigTestName)))
replaceTextPlaceholderInFile(os.path.join(PathToTestDirectory, ("%sBBTestMain.h" % ConfigTestName)))


# adding entry to SctPkg/Config/Data/Category.ini
print "Updating SctPkg/Config/Data/Category.ini..."
if(os.path.isfile("Category.ini.backup")):
    os.remove("Category.ini.backup")
shutil.copyfile(os.path.join(path_to_sctpkg, "Config/Data/Category.ini"), "Category.ini.backup")
if ConfigCategory.name == "ProtocolTest":
    CategoryFileEntry = "\n[Category Data]\nRevision      = 0x00010000\nCategoryGuid  = %s\nInterfaceGuid = %s\nName          = %s\%s\nDescription   = %s\n" % (getHyphenGuid(ConfigTestGuid), getHyphenGuid(ConfigProtocolGuid), ConfigCategory.name, ConfigTestName, ConfigTestDescription)
else:
    CategoryFileEntry = "\n[Category Data]\nRevision      = 0x00010000\nCategoryGuid  = %s\nInterfaceGuid = %s\nName          = %s\%s\nDescription   = %s\n" % (getHyphenGuid(ConfigTestGuid), ConfigCategory.uuid, ConfigCategory.name, ConfigTestName, ConfigTestDescription)
CategoryIni = openFile(os.path.join(path_to_sctpkg, "Config/Data/Category.ini"), "r")
if CategoryIni == None:
    print "ERROR: Could not open \"%s\"" % os.path.join(path_to_sctpkg, "Config/Data/Category.ini")
    faultHandler()
CategoryIniNew = openFile(os.path.join(path_to_sctpkg, "Config/Data/Category.ini.new"), "w")
if CategoryIniNew == None:
    print "ERROR: Could not open \"%s\"" % os.path.join(path_to_sctpkg, "Config/Data/Category.ini.new")
    faultHandler()
CheckPointCreatedNewCategoryIni = True
while True:
    line = CategoryIni.readline()
    if line == "":
        if ConfigCategory.name == "ProtocolTest":
            CategoryIniNew.write(CategoryFileEntry)
        break
    CategoryIniNew.write(line)
    line = line.split()
    if len(line) == 3 and line[0] == "Name" and line[1] == "=" and line[2] == ConfigCategory.name:
        line = CategoryIni.readline()
        CategoryIniNew.write(line)
        CategoryIniNew.write(CategoryFileEntry)
CategoryIni.close()
CategoryIniNew.close()


# adding entry to CommonGenFramework.sh
print "Updating SctPkg/CommonGenFramework.sh"
if os.path.isfile("CommonGenFramework.sh.backup"):
    os.remove("CommonGenFramework.sh.backup")
shutil.copyfile(os.path.join(path_to_sctpkg, "CommonGenFramework.sh"), "CommonGenFramework.sh.backup")
ComGenFwSh = openFile(os.path.join(path_to_sctpkg, "CommonGenFramework.sh"), "r")
if ComGenFwSh == None:
    print "ERROR: Could not open \"%s\"" % os.path.join(path_to_sctpkg, "CommonGenFramework.sh")
    faultHandler()
ComGenFwShNew = openFile(os.path.join(path_to_sctpkg, "CommonGenFramework.sh.new"), "w")
if ComGenFwShNew == None:
    print "ERROR: Could not open \"%s\"" % os.path.join(path_to_sctpkg, "CommonGenFramework.sh.new")
    faultHandler()
CheckPointCreatedNewCommonGenFrameworkSh = True
while True:
    line = ComGenFwSh.readline()
    if line == "":
        break
    ComGenFwShNew.write(line)
    if line.find(ConfigCGFWCategory) != -1:
        while True:
            line = ComGenFwSh.readline()
            if line == "":
                break
            if line[0] == "f" and line[1] == "i" and line[2] == "\n":
                ComGenFwShNew.write("    # automatically generated test entry\n")
                ComGenFwShNew.write("    cp $ProcessorType/%sBBTest.efi    $Framework/Test/  > NUL\n\n" % ConfigTestName)
                ComGenFwShNew.write(line)
                break
            ComGenFwShNew.write(line)
ComGenFwSh.close()
ComGenFwShNew.close()


# finishing up by removing original versions of files and renaming the new ones
os.remove(os.path.join(path_to_sctpkg, "Config/Data/Category.ini"))
os.remove(os.path.join(path_to_sctpkg, "CommonGenFramework.sh"))
os.rename(os.path.join(path_to_sctpkg, "Config/Data/Category.ini.new"), os.path.join(path_to_sctpkg, "Config/Data/Category.ini"))
os.rename(os.path.join(path_to_sctpkg, "CommonGenFramework.sh.new"), os.path.join(path_to_sctpkg, "CommonGenFramework.sh"))
os.system("chmod +x %s" % os.path.join(path_to_sctpkg, "CommonGenFramework.sh"))


# prompting user to modify their DSC file
print ""
print "IMPORTANT: Paste the following line into your projects .dsc file."
print "SctPkg/TestCase/UEFI/EFI/%s/%s/BlackBoxTest/%sBBTest.inf" % (ConfigCategory.path, ConfigTestName, ConfigTestName)
print ""
print "Done, backups of the original Category.ini and CommonGenFramework.sh can be found in the TestCreationScript directory."

sys.exit()
