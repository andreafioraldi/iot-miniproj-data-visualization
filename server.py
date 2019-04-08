#!/usr/bin/env python

from BaseHTTPServer import *
from mimetypes import guess_type
import os

class WasmHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        try:
            if self.path in ("", "/"):
                filepath = "html/bad.html"
            else:
                filepath = self.path.lstrip("/")

            f = open(os.path.join('.', filepath), "rb")

        except IOError:
            self.send_error(404,'File Not Found: %s ' % filepath)

        else:
            self.send_response(200)

            #this part handles the mimetypes for you.
            mimetype, _ = guess_type(filepath)
            if filepath.endswith(".wasm"):
                mimetype = "application/wasm"
            self.send_header('Content-type', mimetype)
            self.end_headers()
            for s in f:
                self.wfile.write(s)

try:
    server = HTTPServer(('localhost', 1234), WasmHandler)
    print("\n >>>> http://localhost:1234/anomalies_map.html\n")
    server.serve_forever()

except KeyboardInterrupt:
    print('^C received, shutting down the web server')
    server.socket.close()
