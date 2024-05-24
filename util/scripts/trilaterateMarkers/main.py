import re
import subprocess
import configparser
from kml import *

ifname = "trilaterate.ini"
ofname = "markers.kml"

if __name__ == "__main__":
    config = configparser.ConfigParser()
    config.read(ifname)

    with open(ofname, "w") as f:
        with kmlWrapper("trilateraiton results", f):
            for section in config.sections():
                with kmlFolder(section, f):
                    for key in config[section]:
                        _type = section.split(":")[-1]
                        name = key.replace("_", " ")
                        match _type:
                            case "point":
                                lat, lon = config[section][key].split(",")
                                marker = getPlaceMark(_type, name, lat, lon)

                            case "circle":
                                marker = getPlaceMark(_type, name, config[section][key])

                            case "line":
                                marker = ""
                                lat1, lon1, lat2, lon2 = [(x) for group in config[section][key].split(" ") for x in group.split(",")]
                                marker = getPlaceMark(_type, name, lat1, lon1, lat2, lon2)

                        f.write(marker)


