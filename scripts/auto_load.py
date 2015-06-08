#!.env/bin/python
import logging
import os
import psutil
import re
import signal
import time

import builder

"""
TODO : handle sig term in child
"""

BIN_NAME = 'eng'
LOG_FILE = '/tmp/auto_load.log'
PID_FILE = '/tmp/auto_load.pid'

def auto_load():
    logging.basicConfig(filename=LOG_FILE, level=logging.INFO, filemode='w')
    
    logging.info('Started auto_load process.')
    start_time = time.time()
    while True:
        time.sleep(5)

        pid = None
        for proc in psutil.process_iter():
            if BIN_NAME in proc.name():
                pid = proc.pid
                logging.info('Watching process with pid {} and name "{}".'.format(pid, proc.name()))

        if pid is None:
            continue

        logging.info('Checking for modifications.')
        modified = False
        
        stages = ['../res/' + s for s in os.listdir('../res') if re.match(r'stage_.+', s)]
        for stage in stages:
            for path, _, files in os.walk(stage):
                for file in files:
                    name = os.path.join(path, file)
                    if '#' not in name and '~' not in name:
                        if os.stat(name).st_mtime >= start_time:
                            logging.info('{} was modified.'.format(name))
                            modified = True

        if modified:
            logging.info('Initiating a reload.')
            builder.main()
            os.kill(pid, signal.SIGUSR1)
            start_time = time.time()

        logging.info('Check complete.')

def main():
    try:
        with open(PID_FILE, 'r') as f:
            old_pid = int(f.read())
        if psutil.pid_exists(old_pid):
            print('An auto_load process already exists.')
            return
    except:
        print('Creating an auto_load process.')

    pid = os.fork()
    if pid == 0:
        auto_load()
    else:
        with open(PID_FILE, 'w') as f:
            f.write(str(pid))

if __name__ == '__main__':
    main()
