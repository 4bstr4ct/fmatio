import os
import sys

root = sys.argv[1]

hpp_files = []
inl_files = []

for r, d, f in os.walk(root):
	for file in f:
		if '.hpp' in file:
			print('adding hpp file: ' + file)
			hpp_files.append(os.path.join(r, file))
		elif '.inl' in file:
			print('adding inl file: ' + file)
			inl_files.append(os.path.join(r, file))

with open('fmatio_all_2.hpp', 'w') as output_file:
	for file in hpp_files:
		with open(file, 'r') as hpp_file:
			content = hpp_file.read()
			output_file.write(content)

	for file in inl_files:
		with open(file, 'r') as inl_file:
			content = inl_file.read()
			output_file.write(content)
