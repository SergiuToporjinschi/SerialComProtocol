try:
    import configparser
except ImportError:
    import ConfigParser as configparser
import shutil, os
print '########### Run pre-build scripts ###########'

config = configparser.ConfigParser()
config.read("platformio.ini")

mainFile = config.get("common", "main_file")

mainPath = "src/main.cpp"
sourcePath = os.getcwd()

def clearMainFile():
    if os.path.exists(mainPath):
        os.remove(mainPath)

def createExamples():
     shutil.copy2("examples/" + mainFile, mainPath)

clearMainFile()
createExamples()

print '########### Finish pre-build scripts ###########'
