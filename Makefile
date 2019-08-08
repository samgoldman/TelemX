CC      := gcc
CFLAGS := -g -Wall -ldl -Wl,--export-dynamic

default: run_sat uplink_files

run_sat: main.o taskManager.o msg.o taskUplink.o taskPatch.o taskShell.o test_functions.o
	$(CC) -o run_sat main.o taskManager.o msg.o taskUplink.o taskPatch.o taskShell.o test_functions.o $(CFLAGS)

main.o: main.c taskManager.h
	$(CC) $(CFLAGS) -c main.c

taskManager.o: taskManager.c taskManager.h tasks.h taskUplink.h
	$(CC) $(CLFAGS) -c taskManager.c

msg.o: msg.c msg.h
	$(CC) $(CFLAGS) -c msg.c

taskUplink.o: taskUplink.c taskUplink.h
	$(CC) $(CFLAGS) -c taskUplink.c

taskPatch.o: taskPatch.c taskPatch.h
	$(CC) $(CFLAGS) -c taskPatch.c

taskShell.o: taskShell.c taskShell.h
	$(CC) $(CFLAGS) -c taskShell.c

test_functions.o: test_functions.c test_functions.h
	$(CC) $(CFLAGS) -c test_functions.c

uplink_files: FORCE
	$(RM) ./uplink/*.cmd
	cp -f ./cmd_examples/0_shell_hello.cmd ./uplink/

clean:
	$(RM) run_sat *.o *~

FORCE:
