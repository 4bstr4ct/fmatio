/*******************************************************************************
 * @file writers.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines writers.hpp implementations.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		BasicFormatWriter<Char>::~BasicFormatWriter() noexcept { };

		template<typename Container>
		BasicDynamicWriter<Container>::BasicDynamicWriter(Container& container) noexcept
			: container(container) { }

		template<typename Container>
		BasicDynamicWriter<Container>::~BasicDynamicWriter() noexcept { }

		template<typename Container>
		void BasicDynamicWriter<Container>::write(BasicStringView<typename Container::CharType> stringified) noexcept
		{
			this->container.append(stringified.getData(), stringified.getSize());
		}
	}
}
