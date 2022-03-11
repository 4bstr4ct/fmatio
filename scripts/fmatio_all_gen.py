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


def get_file(collection, part):
	for x in collection:
		if part in str(x):
			print(x + ' | ' + part)
			return x
	return None


with open('fmatio_all_2.hpp', 'w') as output_file:
	# core.hpp
	core_hpp = get_file(hpp_files, 'core.hpp')
	print(core_hpp)
	if core_hpp is not None:
		with open(core_hpp, 'r') as core_hpp_stream:
			content = core_hpp_stream.read()
			output_file.write(content)
		hpp_files.remove(core_hpp)

	# types.hpp
	types_hpp = get_file(hpp_files, 'types.hpp')
	if types_hpp is not None:
		with open(types_hpp, 'r') as types_hpp_stream:
			content = types_hpp_stream.read()
			output_file.write(content)
		hpp_files.remove(types_hpp)

	
	for file in hpp_files:
		with open(file, 'r') as hpp_file:
			content = hpp_file.read()
			output_file.write(content)

	for file in inl_files:
		with open(file, 'r') as inl_file:
			content = inl_file.read()
			output_file.write(content)
