#pragma once

#include <Common/config.h>

#if USE_HDFS
#include <IO/ReadBuffer.h>
#include <IO/BufferWithOwnMemory.h>
#include <string>
#include <memory>

namespace DB
{
/** Accepts path to file and opens it, or pre-opened file descriptor.
 * Closes file by himself (thus "owns" a file descriptor).
 */
class ReadBufferFromHDFS : public BufferWithOwnMemory<ReadBuffer>
{
    struct ReadBufferFromHDFSImpl;
    std::unique_ptr<ReadBufferFromHDFSImpl> impl;
public:
    ReadBufferFromHDFS(const std::string & hdfs_name_, size_t buf_size = DBMS_DEFAULT_BUFFER_SIZE);
    ReadBufferFromHDFS(ReadBufferFromHDFS &&) = default;

    bool nextImpl() override;

    ~ReadBufferFromHDFS() override;

    const std::string & getHDFSUri() const;
};
}
#endif
