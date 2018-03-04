import requests
import sys
import json




for i in range(100000):
    result = requests.get('http://localhost:18080/json')
    if result.status_code == 200:
        print result.text
    else:
        print "Failed :: result code == %s" % (result.status_code)
        sys.exit(1);
