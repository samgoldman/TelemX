#!/usr/bin/python3

from shutil import copyfile


def main():
	while True:
		a = input( 
"""
0) Send shell command: execute hello_world()
1) Send shell command: execute goodbye_world()
2) Send patch command: replace return of goodbye_world() with 0xaabbccdd
3) Send patch command: replace return of goodbye_world() with user defined value
""")
		if a == "0":
			copyfile("./cmd_examples/0_shell_hello.cmd", "./uplink/0_shell_hello.cmd")
		elif a == "1":
			copyfile("./cmd_examples/1_shell_goodbye.cmd", "./uplink/1_shell_goodbye.cmd")
		elif a == "2":
			copyfile("./cmd_examples/2_patch_goodbye.cmd", "./uplink/2_patch_goodbye.cmd")
		elif a == "3":
			b = int(input("Custom value (decimal integer, 32 bits): "))
			data = bytearray(2052)
			data[0] = 0x64
			data[4] = 0x00
			data[5] = 0x06
			data[8] = 0x04

			custom_ba = bytes.fromhex(hex(b)[2:])
			data[12] = custom_ba[0]
			data[13] = custom_ba[1]
			data[14] = custom_ba[2]
			data[15] = custom_ba[3]

			with open('./uplink/custom_patch.cmd', 'wb') as file:
				file.write(data)


if __name__ == '__main__':
	main()
