#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
namespace swaw::slutcom {

    enum PacketType : std::uint8_t { GyroData = 0x1, AccelData = 0x2 };

    struct Packet {
        constexpr static std::uint8_t preamble[2]{0xFF, 0xFF}; // Packet preamble
        constexpr static std::uint8_t sop = 0xAB;              // Start of packet delimiter
        PacketType                    type;
        std::uint16_t                 crc{};

        // Constructor that initializes packet type
        constexpr Packet(PacketType t) : type(t) {
        }

        virtual ~Packet() = default;

        /// Returns size of the packet, as it would be serialized
        constexpr std::size_t size() const {
            return sizeof(preamble) + sizeof(sop) + sizeof(type) + sizeof(crc) + getPayloadSize();
        }

        /// Serializes Packet into memory region d
        constexpr std::span<char> serialize(std::span<char> d) const {
            // Check whether d will be able to store the serialized packet
            if (d.size() >= size() && isValid()) {
                auto serializer(d);
                // Copy preamble and SOP
                std::memcpy(serializer.data(), preamble, sizeof(preamble));
                serializer = serializer.subspan(sizeof(preamble));
                std::memcpy(serializer.data(), &sop, sizeof(sop));
                serializer = serializer.subspan(sizeof(sop));

                // Start checksum calculation
                auto checksumTmp = checksum_calculate({reinterpret_cast<char const*>(&type), sizeof(type)});
                serializer[0]    = type;

                // Serialize payload and calculate its checksum
                serializer   = serializer.subspan(sizeof(type));
                auto crcData = serializer;
                serializer = serializer.subspan(sizeof(crc));
                serializePayload(serializer);
                checksumTmp += checksum_calculate(serializer.subspan(0, getPayloadSize()));


                // Copy checksum into the buffer
                auto checksum = checksum_finalize(checksumTmp);
                std::memcpy(crcData.data(), &checksum, sizeof(checksum));

                return d.subspan(0, size());
            }
            return {};
        }


      private:
        /// Performs packet-specific checks, and returns logical value whether the packet contains valid data
        constexpr virtual bool isValid() const = 0;

        /// Returns size of the payload (excluding header)
        constexpr virtual std::size_t getPayloadSize() const = 0;

        /// Serializes the payload into the memory region d
        constexpr virtual void serializePayload(std::span<char> d) const = 0;

        /**
         *  @brief Calculates Compliment 1 checksum from given data
         *
         * To calculate checksum of non adjacent memory chunks, one should sum the partial checksum for each chunk, and then call checksum_finalize
         * @param[] d data to calculate checksum from
         * @return Partial checksum of data. To obtain final value it has to be finalized using @ref checksum_finalize
         */
        constexpr static std::uint32_t checksum_calculate(std::span<char const> d) {
            std::uint32_t sum = 0;

            for (std::size_t i = 0; i != d.size(); ++i) {
                if (i & 1)
                    sum += static_cast<std::uint32_t>(d[i]);
                else
                    sum += static_cast<std::uint32_t>(static_cast<std::uint32_t>(d[i]) << 8U);
            }
            return sum;
        }


        /**
         * @brief Converts partial checksum into final one
         *
         * @param[in] sum partial checksum
         * @return final complimented 1s checksum
         */
        constexpr static std::uint16_t checksum_finalize(std::uint32_t sum) {
            while (static_cast<std::uint32_t>(sum >> 16U) != 0) {
                sum = static_cast<std::uint32_t>(static_cast<std::uint32_t>(sum & 0xFFFF) + static_cast<std::uint32_t>(sum >> 16U));
            }
            return static_cast<std::uint16_t>(~sum);
        }
    };


    struct AccelerationPacket : public Packet {
        // todo add data fields
        std::int32_t x;
        std::int32_t y;
        std::int32_t z;

        // todo add constructor that initializes data fields in both AccelerationPacket, and its base class
        AccelerationPacket(std::int32_t _x, std::int32_t _y, std::int32_t _z):Packet(AccelData) {
            x = _x;
            y = _y;
            z = _z;
        }

      private:
        constexpr bool isValid() const override {
            return true; // Based on data, we are unable to determine whether this packet is valid
        }


        constexpr std::size_t getPayloadSize() const override {
            // todo get size of data fields
            return (sizeof(x) + sizeof(y) + sizeof(z));
        }

        constexpr void serializePayload(std::span<char> d) const override {
            // todo copy data fields (in order) into the memory region pointed by d
            std::memcpy(d.data(), &x, sizeof(x));
            d = d.subspan(sizeof(x));
            std::memcpy(d.data(), &y, sizeof(y));
            d = d.subspan(sizeof(y));
            std::memcpy(d.data(), &z, sizeof(z));
            d = d.subspan(sizeof(z));
            return;
        }
    };

    struct GyroscopePacket : public Packet {
        // todo add data fields
        std::int32_t x;
        std::int32_t y;
        std::int32_t z;

        // todo add constructor that initializes data fields in both GyroscopePacket, and its base class
        GyroscopePacket(std::int32_t _x, std::int32_t _y, std::int32_t _z):Packet(GyroData) {
            x = _x;
            y = _y;
            z = _z;
        }

      private:
        constexpr bool isValid() const override {
            return true; // Based on data, we are unable to determine whether this packet is valid
        }


        constexpr std::size_t getPayloadSize() const override {
            // todo get size of data fields
            return (sizeof(x) + sizeof(y) + sizeof(z));
        }

        constexpr void serializePayload(std::span<char> d) const override {
            // todo copy data fields (in order) into the memory region pointed by d
            std::memcpy(d.data(), &x, sizeof(x));
            d = d.subspan(sizeof(x));
            std::memcpy(d.data(), &y, sizeof(y));
            d = d.subspan(sizeof(y));
            std::memcpy(d.data(), &z, sizeof(z));
            d = d.subspan(sizeof(z));
            return;
        }
    };

} // namespace swaw::slutcom